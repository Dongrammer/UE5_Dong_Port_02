#include "Component/SoulComponent.h"

#include "Character/Hero.h"
#include "Widget/Soul/SoulHUD.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY(SoulCompLog);

USoulComponent::USoulComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USoulComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AHero>(GetOwner());
	if (!OwnerCharacter)
	{ 
		UE_LOG(SoulCompLog, Warning, TEXT("Hero Is NULL"));
		return;
	}

	// Create HUD
	if (!SoulHUDClass)
	{
		UE_LOG(SoulCompLog, Warning, TEXT("SoulHUDClass Is NULL !!"));
		return;
	}

	PlayerController = Cast<APlayerController>(OwnerCharacter->GetController()); // 주의!!! GetPlayerController로 가져오면 NULL을 가져옴!
	if (!PlayerController)
	{
		UE_LOG(SoulCompLog, Warning, TEXT("PlayerController Is NULL !!"));
		return;
	}

	SoulHUD = CreateWidget<USoulHUD>(PlayerController, SoulHUDClass, "Soul HUD");
	if (!SoulHUD)
	{
		UE_LOG(SoulCompLog, Warning, TEXT("SoulHUD Is NULL !!"));
		return;
	}

	SoulHUD->AddToViewport();
	SoulHUD->SetVisibility(ESlateVisibility::Hidden);
}

void USoulComponent::SetSoulGage()
{
	// Check Gage
	if (CurrentSoulGage <= 0)
	{
		SoulLevel = 0;
		OwnerCharacter->GetWorldTimerManager().ClearTimer(SetGageTimer);

		// Destroy Trail
		if (TrailComponent)
		{
			TrailComponent->DestroyComponent();
			TrailComponent = nullptr;
		}

		// Init PlayRate
		OwnerCharacter->InitWalkSpeed(); // 이후 다른 컴포넌트에서 PlayRate를 건드릴 경우에는 컴포넌트마다 PlayRate가 있고, 중앙에서 합산하는 방식으로 바꿔야함.
		OwnerCharacter->SetPlayRate(1.0f);

		// Soul Recovery
		OwnerCharacter->GetWorldTimerManager().SetTimer(RecoveryTimer, this, &USoulComponent::SoulRecovery, 0.1f, true);
	}

	// Setting Gage
	switch (SoulLevel)
	{
	case 1:
	{
		CurrentSoulGage -= 0.1;
		break;
	}
	case 2:
	{
		CurrentSoulGage -= 0.2;
		break;
	}
	case 3:
	{
		CurrentSoulGage -= 0.4;
		break;
	}
	default:
		break;
	}

	// Setting HUD
	SoulHUD->SetSouleGage(MaxSoulGage, CurrentSoulGage);
}

void USoulComponent::NiagaraSetting()
{
	// Explosion
	if (!NS_SoulBurnExplosion)
	{
		UE_LOG(SoulCompLog, Warning, TEXT("NS_SoulBurnExplosion Is NULL !!"));
		return;
	}

	float scale = 1.0f;
	switch (SoulLevel)
	{
	case 1:
	{
		scale = 0.3f;
		break;
	}
	case 2:
	{
		scale = 0.6f;
		break;
	}
	case 3:
	{
		scale = 1.0f;
		break;
	}
	default:
		break;
	}
	TObjectPtr<UNiagaraComponent> ExplosionComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_SoulBurnExplosion, OwnerCharacter->GetActorLocation(), FRotator(0, 0, 0));
	ExplosionComponent->SetFloatParameter(FName("Scale"), scale);

	// Trail
	if (SoulLevel > NS_SoulBurnTrail.Num())
	{
		UE_LOG(SoulCompLog, Warning, TEXT("NS_SoulBurnTrail Num Over"));
		return;
	}

	TObjectPtr<UNiagaraSystem> trail = NS_SoulBurnTrail[SoulLevel - 1];

	if (!trail)
	{
		UE_LOG(SoulCompLog, Warning, TEXT("NS_SoulBurnTrail Is NULL !!"))
		return;
	}

	EWeaponType wtype = OwnerCharacter->GetCurrentWeaponType();
	FName SocketName = "";
	switch (wtype)
	{
	case EWeaponType::E_None:
		break;
	case EWeaponType::E_Gauntlet:
	{
		SocketName = "Gauntlet_Trail_Start";
		break;
	}
	case EWeaponType::E_OneHandSword:
	{
		SocketName = "OneHandSword_Trail_Start";
		break;
	}
	case EWeaponType::E_Max:
		break;
	default:
		break;
	}
	FVector Location = FVector(0, 0, 0);
	FRotator Rotation = FRotator(0, 0, 0);
	
	if (trail)
		TrailComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(trail, OwnerCharacter->GetMesh(), SocketName, Location, Rotation, EAttachLocation::KeepRelativeOffset, true);
}

void USoulComponent::SoulRecovery()
{
	if (CurrentSoulGage >= MaxSoulGage)
	{
		CurrentSoulGage = MaxSoulGage;
		OwnerCharacter->GetWorldTimerManager().ClearTimer(RecoveryTimer);
		SoulHUD->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	CurrentSoulGage += RecoveryGage;
	SoulHUD->SetSouleGage(MaxSoulGage, CurrentSoulGage);
}

void USoulComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USoulComponent::SoulBurn()
{
	SetSoulGage();

	// Stop Recovery
	OwnerCharacter->GetWorldTimerManager().ClearTimer(RecoveryTimer);

	// Check Safe
	if (!SoulBurnAnim) 
	{ 
		UE_LOG(SoulCompLog, Warning, TEXT("SoulBurnAnim Is NULL !!"));
		return; 
	}

	// Check State
	if (!OwnerCharacter->CurrentStateIs(EStateType::E_Idle) && !OwnerCharacter->CurrentStateIs(EStateType::E_Attack)) return;
	OwnerCharacter->InitState();

	// Check Level
	if (SoulLevel >= MaxSoulLevel) return;

	// Play
	OwnerCharacter->PlayAnimMontage(SoulBurnAnim);
	
	SoulLevel++;

	OwnerCharacter->GetWorldTimerManager().SetTimer(SetGageTimer, this, &USoulComponent::SetSoulGage, 0.1f, true);
	
	SoulHUD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	// Niagara
	if (TrailComponent)
	{
		TrailComponent->DestroyComponent();
		TrailComponent = nullptr;
	}

	NiagaraSetting();

	// Camera Shake
	if (CS_SoulBurn)
	{
		float scale = 1.0f;
		switch (SoulLevel)
		{
		case 1:
		{
			scale = 0.5f;
			break;
		}
		case 2:
		{
			scale = 1.0f;
			break;
		}
		case 3:
		{
			scale = 1.5f;
		}
		}

		PlayerController->ClientStartCameraShake(CS_SoulBurn, scale);
	}

	// Set Character PlayRate, Movement
	float PlayRate = 1.0f;
	switch (SoulLevel)
	{
	case 1:
	{
		PlayRate = 1.2f;
		break;
	}
	case 2:
	{
		PlayRate = 1.4f;
		break;
	}
	case 3:
	{
		PlayRate = 1.6f;
		break;
	}
	default:
		break;
	}
	OwnerCharacter->SetPlayRate(PlayRate);

}

