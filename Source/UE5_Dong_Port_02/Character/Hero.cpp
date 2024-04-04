#include "Character/Hero.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Helper.h"
#include "InputDataAsset.h"
#include "../Component/InventoryComponent.h"
#include "Item/BaseItem.h"
#include "Components/CapsuleComponent.h"
#include "Widget/Inventory/InventoryHUD.h"
#include "Blueprint/UserWidget.h"
#include "Item/BaseItem.h"

DEFINE_LOG_CATEGORY(HeroLog);

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	CreateCamera();
	CreateCharacter();
	InvenHUDClass = Helper::GetClass<UInventoryHUD>(L"/Game/Widget/Inventory/WB_Inventory");
}

void AHero::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AHero::CreateCharacter()
{
	Super::CreateCharacter();

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>(L"/Game/Characters/Hero/ABP_Hero"));
}

void AHero::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();	// 카메라 움직임 용 모든 축 회전값
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// 캐릭터 움직임 용 Y축 회전값

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHero::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void AHero::DoInteraction()
{
	Interaction = true;
}

void AHero::EndInteraction()
{
	Interaction = false;
}

void AHero::WeaponStartUp()
{
}

void AHero::DoMainAction()
{
}

void AHero::EndMainAction()
{
}

void AHero::DoSubAction()
{
}

void AHero::EndSubAction()
{
}

void AHero::DoAvoid()
{
	Jump();
}

void AHero::EndAvoid()
{
}

void AHero::InventoryOn()
{
}

void AHero::QuickSlotWheel()
{
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (SubSystem != nullptr)
		{
			SubSystem->AddMappingContext(KeyMappingContext, 0);
		}
	}

	BodyCollision->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnBeginOverlap);
	BodyCollision->OnComponentEndOverlap.AddDynamic(this, &AHero::OnEndOverlap);

	/* ========== Widget ========== */

	// Inventory HUD
	if (InvenHUDClass == nullptr)
	{
		UE_LOG(HeroLog, Warning, TEXT("InvenHUDClass Is NULL!!"));
		return;
	}

	InvenHUD = CreateWidget<UInventoryHUD>(Cast<APlayerController>(GetController()), InvenHUDClass, "Inventory HUD");

	// 임시
	//InvenHUD->AddToViewport();
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent == nullptr) return;
	MappingInputAsset(EnhancedInputComponent);
}

void AHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 300.0f;
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetRelativeLocation(FVector(0, 30, 150));

	Camera = Helper::CreateSceneComponent<UCameraComponent>(this, "Camera", CameraArm);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeRotation(FRotator(-10, 0, 0));
}

void AHero::MappingInputAsset(UEnhancedInputComponent* Comp)
{
	if (!InputAsset)
	{
		UE_LOG(HeroLog, Log, TEXT("Input Asset is Null Check BP_Hero"));
		return;
	}

	// Movement
	MAPPING_TRIGGERED(Comp, InputAsset->LookInput, AHero::Look);
	MAPPING_TRIGGERED(Comp, InputAsset->MoveInput, AHero::Move);

	// Actions
	MAPPING_CLICK(Comp, InputAsset->Interaction, AHero::DoInteraction, AHero::EndInteraction);
	MAPPING_CLICK(Comp, InputAsset->AvoidAction, AHero::DoAvoid, AHero::EndAvoid);
	//MAPPING_CLICK(Comp, InputAsset->MainAction, AHero::DoMainAction, AHero::EndMainAction);
	//MAPPING_CLICK(Comp, InputAsset->SubAction, AHero::DoSubAction, AHero::EndSubAction);

	//// Weapon
	//MAPPING_TRIGGERED(Comp, InputAsset->WeaponStartUp, AHero::WeaponStartUp);

	//// Inventory
	//MAPPING_TRIGGERED(Comp, InputAsset->InventoryOn, AHero::InventoryOn);
	//MAPPING_TRIGGERED(Comp, InputAsset->QuickSlotWheel, AHero::QuickSlotWheel);
}

void AHero::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check Item
	TObjectPtr<ABaseItem> Item = Cast<ABaseItem>(OtherComp->GetOwner());

	if (Item)
	{
		Item->TextOnOff();
		Item->AccessPlayer = this;
	}
}

void AHero::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check Item
	TObjectPtr<ABaseItem> Item = Cast<ABaseItem>(OtherComp->GetOwner());

	if (Item)
	{
		UE_LOG(HeroLog, Log, TEXT("Overlap Item : %s"), Item->Name);
		Item->TextOnOff();
		Item->AccessPlayer = nullptr;
	}
}
