#include "BaseCharacter.h"

#include "TPS_GameInstance.h"

//#include "Component/ItemComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Item/BaseItem.h"
#include "Helper.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = GetCapsuleComponent();
	SetCharacterMovement();

	StatusComponent = Helper::CreateActorComponent<UStatusComponent>(this, "Status Component");
	HittedPoints = Helper::CreateSceneComponent<USceneComponent>(this, "Hitted Points", BodyCollision);
	//ItemComponent = Helper::CreateActorComponent<UItemComponent>(this, "Item Component");

	// Widget
	HealthBarClass = Helper::GetClass<UNPCHealthBar>(L"/Game/Widget/NPC/WB_NPCHealthBar");

	if (!HealthBarClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter : HealthBarClass Is NULL !!"));
		return;
	}

	HealthBarWidgetComp = Helper::CreateSceneComponent<UWidgetComponent>(this, TEXT("Health Bar WidgetComp"), BodyCollision);
	HealthBarWidgetComp->SetWidgetClass(HealthBarClass);
	HealthBarWidgetComp->SetRelativeLocation(FVector(0, 0, 120));
	HealthBarWidgetComp->SetDrawSize(FVector2D(100, 5));
	HealthBarWidgetComp->SetCastShadow(false);

	DamageFloatingWidgetClass = Helper::GetClass<ADamageFloatingActor>(L"/Game/Widget/Battle/BP_DamageFloatingActor.BP_DamageFloatingActor");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Time
	GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Instance Is NULL !!"));
		return;
	}

	GameInstance->DOneMinuteTimePass.AddUFunction(this, "OneMinuteTimePass");
	// Widget
	HealthBarWidgetComp->SetVisibility(false);
	TObjectPtr<UUserWidget> widget = HealthBarWidgetComp->GetUserWidgetObject();
	if (!widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter : widget Is NULL !!"));
	}
	HealthBarWidgetComp->SetVisibility(false);
	TObjectPtr<UUserWidget> widget2 = HealthBarWidgetComp->GetWidget();
	if (!widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter : widget2 Is NULL !!"));
	}
	//HealthBar = Cast<UNPCHealthBar>(HealthBarWidget->GetUserWidgetObject());
	HealthBar = Cast<UNPCHealthBar>(HealthBarWidgetComp->GetWidget());
	
	if (!HealthBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter : HealthBar Is NULL !!"));
		return;
	}
	HealthBar->SetHealthPercent(1.0f);

	TObjectPtr<APlayerController> playercont = GetWorld()->GetFirstPlayerController();
	if (!playercont)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseCharacter : PlayerController Is NULL !!"));
		return;
	}

	playerCamera = playercont->GetPawn()->GetComponentByClass<UCameraComponent>();
	if (!playerCamera)
	{
		UE_LOG(LogTemp, Log, TEXT("ABaseCharacter : PlayerCamera Is NULL !!"));
		return;
	}
}

void ABaseCharacter::CreateCharacter()
{
}

void ABaseCharacter::SetCharacterMovement()
{
	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = true;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 600.0f;
	StandardWalkSpeed = Comp->MaxWalkSpeed;

	// 멈췄을 때 감속
	Comp->BrakingDecelerationWalking = 2000.0f;
	// 떨어질 때 감속
	//Comp->BrakingDecelerationFalling = 1500.0f;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UI
	if (HealthBarWidgetComp)
	{
		if (HealthBarWidgetComp->IsVisible())
		{
			if (playerCamera)
			{
				FRotator newRo = playerCamera->GetComponentRotation() + FRotator(180, 0, 180);
				HealthBarWidgetComp->SetWorldRotation(newRo);
			}
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::GetCapsuleRadius()
{
	return BodyCollision->GetScaledCapsuleRadius();
}

void ABaseCharacter::SetWalkSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ABaseCharacter::InitWalkSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = StandardWalkSpeed;
}

void ABaseCharacter::InitState()
{
	SetCanMove(true);
	SetCanAttack(true);
	SetCurrentState(EStateType::E_Idle);
	SetEffectState(EStateEffectType::E_None);
}

void ABaseCharacter::SetRagdoll()
{
	BodyCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetWorld()->GetTimerManager().SetTimer(DeadTimer, this, &ABaseCharacter::DeadRemove, 5.0f, false, 5.0f);
}

void ABaseCharacter::DeadRemove()
{
	this->Destroy();
}

void ABaseCharacter::SetEffectState(EStateEffectType type)
{
	StatusComponent->SetCurrentEffectState(type);
	
	if (type == EStateEffectType::E_Freezing)
	{
		SetCanMove(false);
		SetCanAttack(false);
	}
	else
	{
		SetCanMove(true);
		SetCanAttack(true);
	}
}

void ABaseCharacter::TakeDamageFuc(AActor* damagecauser, int damage, FVector hittedlocation)
{
	TObjectPtr<ABaseCharacter> causer = Cast<ABaseCharacter>(damagecauser);
	if (causer)
	{
		FightingCharacter = causer;
		CurrentFighting = true;
	}

	if (!HealthBar) return;
	StatusComponent->UpdateHP(damage);
	float percent = (float)StatusComponent->GetTotalStatus().HP / (float)StatusComponent->GetTotalStatus().MHP;
	HealthBar->SetHealthPercent(percent);
	HealthBarVisible();

	if (DamageFloatingWidgetClass)
	{
		FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 30);
		FRotator SpawnRotation = playerCamera->GetComponentRotation() + FRotator(180, 0, 180);
		TObjectPtr<ADamageFloatingActor> damagefloatingwidget = GetWorld()->SpawnActor<ADamageFloatingActor>(DamageFloatingWidgetClass, SpawnLocation, SpawnRotation);
		damagefloatingwidget->ActiveWidget(damage);
	}
}

void ABaseCharacter::TakeEffectDamageFuc(EStateEffectType type, int val)
{
	// 이후 저항력 관련 함수와 상태이상 데미지 연산
	switch (type)
	{
	case EStateEffectType::E_Freezing:
	{
		SetEffectState(type);
		break;
	}
	case EStateEffectType::E_Burn:
	{
		SetEffectState(type);
		break;
	}
	default:
		break;
	}
}

void ABaseCharacter::OneMinuteTimePass()
{
	GlobalTime = GameInstance->GetGlobalTime();
}

void ABaseCharacter::HealthBarVisible()
{
	if (!HealthBarWidgetComp->IsVisible())
	{
		HealthBarWidgetComp->SetVisibility(true);
		HealthBar->PlayVisibleAnim();
	}

	HealthBar->PlayInvisibleAnim();
	GetWorld()->GetTimerManager().SetTimer(HealthBarInvisibleHandle, this, &ABaseCharacter::HealthBarInvisible, 10.0f);
}

void ABaseCharacter::HealthBarInvisible()
{
	HealthBarWidgetComp->SetVisibility(false);
	GetWorld()->GetTimerManager().ClearTimer(HealthBarInvisibleHandle);
}

void ABaseCharacter::UpdateAttack(int val)
{
	StatusComponent->UpdateAttack(val);
}

void ABaseCharacter::GetEXP(int val)
{
	StatusComponent->GetEXP(val);
}

void ABaseCharacter::LevelUp()
{
	StatusComponent->LevelUp();
}
