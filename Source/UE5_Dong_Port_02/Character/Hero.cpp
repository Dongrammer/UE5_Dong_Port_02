#include "Character/Hero.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Helper.h"
#include "InputDataAsset.h"
#include "../Component/InventoryComponent.h"
#include "../Component/TechniqueComponent.h"
#include "../Component/ActionComponent.h"
#include "../Component/WeaponComponent.h"
#include "Item/BaseItem.h"
#include "Components/CapsuleComponent.h"
#include "Widget/Inventory/InventoryHUD.h"
#include "Blueprint/UserWidget.h"
#include "Item/BaseItem.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(HeroLog);

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationYaw = false;
	CreateCamera();
	CreateCharacter();
	InvenHUDClass = Helper::GetClass<UInventoryHUD>(L"/Game/Widget/Inventory/WB_Inventory");
	hero = this;
	TechniqueComponent = Helper::CreateActorComponent<UTechniqueComponent>(this, "Technique Component");
	ActionComponent = Helper::CreateActorComponent<UActionComponent>(this, "Action Component");
	ActionComponent->SetOwner(this);
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
		const FRotator Rotation = Controller->GetControlRotation();	// ī�޶� ������ �� ��� �� ȸ����
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// ĳ���� ������ �� Y�� ȸ����

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
	bInteraction = true;
}

void AHero::EndInteraction()
{
	bInteraction = false;
}

void AHero::WeaponStartUp()
{
}

void AHero::DoMainAction()
{
	if (WeaponComponent->GetWeaponHolding() && bCanAttack)
	{
		ActionComponent->DoAction();
	}
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
	InventoryComponent->ToggleInventory();
}

void AHero::QuickSlotWheel()
{
}

void AHero::TechniqueOn()
{
	TechniqueComponent->ToggleHUD();
}

void AHero::EquipWeapon()
{
	UE_LOG(LogTemp, Log, TEXT("EquipWeapon Call"));
	if (!WeaponComponent) return;

	if (WeaponComponent->bHolding) WeaponComponent->bHolding = false;
	else if (!WeaponComponent->bHolding) WeaponComponent->bHolding = true;
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetOwner());

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

	InvenHUD = CreateWidget<UInventoryHUD>(PlayerController, InvenHUDClass, "Inventory HUD");
	InvenHUD->AddToViewport();
	InvenHUD->SetVisibility(ESlateVisibility::Hidden);
	InventoryComponent->InvenHUD = InvenHUD;
	InventoryComponent->InvenHUDSetting();

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
	MAPPING_CLICK(Comp, InputAsset->MainAction, AHero::DoMainAction, AHero::EndMainAction);
	//MAPPING_CLICK(Comp, InputAsset->SubAction, AHero::DoSubAction, AHero::EndSubAction);

	//// Weapon
	//MAPPING_TRIGGERED(Comp, InputAsset->WeaponStartUp, AHero::WeaponStartUp);
	Comp->BindAction(InputAsset->EquipWeapon, ETriggerEvent::Started, this, &AHero::EquipWeapon);

	// Inventory
	Comp->BindAction(InputAsset->InventoryOn, ETriggerEvent::Started, this, &AHero::InventoryOn);
	//MAPPING_TRIGGERED(Comp, InputAsset->QuickSlotWheel, AHero::QuickSlotWheel);

	// Technique
	Comp->BindAction(InputAsset->TechniqueOn, ETriggerEvent::Started, this, &AHero::TechniqueOn);
}

void AHero::SetMouseState(bool visibility, EInputModeType inputmode, UWidget* widget)
{
	APlayerController* cont = Cast<APlayerController>(GetController());

	switch (inputmode)
	{
	case EInputModeType::E_GameOnly:
	{
		FInputModeGameOnly InputMode;
		cont->SetInputMode(InputMode);
		break;
	}
	case EInputModeType::E_GameAndUIOnly:
	{
		if (!widget)
		{
			UE_LOG(HeroLog, Warning, TEXT("SetMouseState : Widget Is NULL !!"));
			break;
		}

		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(widget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 마우스를 눌렀을 때 위치가 고정되지 않도록
		InputMode.SetHideCursorDuringCapture(false);
		cont->SetInputMode(InputMode);
		break;
	}
	case EInputModeType::E_UIOnly:
	{
		if (!widget)
		{
			UE_LOG(HeroLog, Warning, TEXT("SetMouseState : Widget Is NULL !!"));
			break;
		}

		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(widget->TakeWidget());
		cont->SetInputMode(InputMode);
		break;
	}
	default:
	{
		UE_LOG(HeroLog, Warning, TEXT("SetMouseState : EInputMode Not Valid"));
		break;
	}
	}

	cont->SetShowMouseCursor(visibility);
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
		Item->TextOnOff();
		Item->AccessPlayer = nullptr;
	}
}
