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
#include "../Component/SoulComponent.h"
#include "../Component/EquipComponent.h"
#include "Item/BaseItem.h"
#include "Components/CapsuleComponent.h"
#include "Widget/MainHUD.h"
// MainHUD만 포함하고 다른 HUD는 MainHUD의 헤더에 포함시킬지 고민.
#include "Widget/Inventory/InventoryHUD.h"
#include "Widget/Inventory/InventoryContextMenu.h"
#include "Widget/Equipment/EquipmentHUD.h"
#include "Widget/InteractionHUD.h"
#include "Widget/Status/StatusHUD.h"
#include "Blueprint/UserWidget.h"
#include "Item/BaseItem.h"
#include "Kismet/GameplayStatics.h" // 월드 행렬을 뷰포트 행렬로 바꾸기 위해 필요
//#include "TPS_GameInstance.h"
#include "Land/Prob/BaseProb.h"

DEFINE_LOG_CATEGORY(HeroLog);

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationYaw = false;
	CreateCamera();
	CreateCharacter();
	InvenHUDClass = Helper::GetClass<UInventoryHUD>(L"/Game/Widget/Inventory/WB_Inventory");
	hero = this;
	ActionComponent = Helper::CreateActorComponent<UActionComponent>(this, "Action Component");
	TechniqueComponent = Helper::CreateActorComponent<UTechniqueComponent>(this, "Technique Component");
	// ActionComponent가 TechniqueComponent보다 위에 있어야함. ActionComponent에 CreateAction이 먼저 실행되어야 하기 때문.
	SoulComponent = Helper::CreateActorComponent<USoulComponent>(this, "Soul Component");
	
	// InteractionCapsule
	InteractionCapsule = Helper::CreateActorComponent<UCapsuleComponent>(this, "Interaction Capsule");
	InteractionCapsule->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	InteractionCapsule->SetRelativeLocation(FVector(410, 0, -25));
	InteractionCapsule->SetRelativeRotation(FRotator(0, -90, 0));
	InteractionCapsule->SetRelativeScale3D(FVector(1.5, 1.5, 2));
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
	
	// Set InputDirection
	if (MovementVector.Y > 0) inputDirection = EInputDirection::E_Forward;
	else if (MovementVector.Y < 0) inputDirection = EInputDirection::E_Back;
	else if (MovementVector.X > 0) inputDirection = EInputDirection::E_Right;
	else if (MovementVector.X < 0) inputDirection = EInputDirection::E_Left;
	else inputDirection = EInputDirection::E_Forward;

	// Check CanMove
	if (bCanMove == false) return;
	if (!Controller) return;

	// Movement

	const FRotator Rotation = Controller->GetControlRotation();	// ī�޶� ������ �� ��� �� ȸ����
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// ĳ���� ������ �� Y�� ȸ����

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
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
	//bInteraction = true;
	if (InteractionItem)
	{
		GetItems(InteractionItem->itemdata, 1);
		InteractionItem->Destroy();
	}

	if (InteractionProb)
	{
		InteractionProb->Active();
	}
}

void AHero::EndInteraction()
{
	//bInteraction = false;
}

void AHero::WeaponStartUp()
{
}

void AHero::DoMainAction()
{
	bLeftClicked = true;

	if (WeaponComponent->GetWeaponHolding() && bCanAttack)
	{
		ActionComponent->DoAction();
	}
}

void AHero::EndMainAction()
{
	bLeftClicked = false;

	if (WeaponComponent->GetWeaponHolding())
	{
		ActionComponent->EndAction();
	}
}

void AHero::DoSubAction()
{
}

void AHero::EndSubAction()
{
}

void AHero::PressedAvoid()
{
	TArray<EStateType> state;
	state.Add(EStateType::E_Idle);
	state.Add(EStateType::E_Attack);

	if (GetWeaponHolding() && CurrentStateAre(state))
	{
		ActionComponent->PressedAvoid();
	}
	else if (!GetWeaponHolding() && CurrentStateIs(EStateType::E_Idle))
		Jump();
}

void AHero::ReleasedAvoid()
{
	ActionComponent->ReleasedAvoid();
}

void AHero::InventoryOn()
{
	if (TechniqueComponent->GetHUDVisible()) return;

	if (!MainHUD->CheckHUDsVisibility())
		SetMouseCenter();

	MainHUD->ToggleInvenHUD();

	if (MainHUD->CheckHUDsVisibility())
	{
		MainHUD->SetVisibility(ESlateVisibility::Visible);
		SetMouseState(true, EInputModeType::E_GameAndUIOnly, MainHUD);
	}
	else
	{
		MainHUD->SetVisibility(ESlateVisibility::Hidden);
		SetMouseState(false, EInputModeType::E_GameOnly);
	}
}

void AHero::QuickSlotWheel()
{
}

void AHero::TechniqueOn()
{
	TechniqueComponent->ToggleHUD();

	if (MainHUD->IsVisible())
	{
		MainHUD->SetAllHidden();
		MainHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHero::EquipWeapon()
{
	if (!WeaponComponent) return;

	if (WeaponComponent->bHolding)
	{
		WeaponComponent->bHolding = false;
		bUseControllerRotationYaw = false;
	}
	else if (!WeaponComponent->bHolding)
	{
		WeaponComponent->bHolding = true;
		bUseControllerRotationYaw = true;
	}
}

void AHero::SoulBurn()
{
	SoulComponent->SoulBurn();
}

void AHero::EquipmentOn()
{
	if (TechniqueComponent->GetHUDVisible()) return;
	if (!MainHUD->CheckHUDsVisibility())
		SetMouseCenter();

	MainHUD->ToggleEquipHUD();

	if (MainHUD->CheckHUDsVisibility())
	{
		MainHUD->SetVisibility(ESlateVisibility::Visible);
		SetMouseState(true, EInputModeType::E_GameAndUIOnly, MainHUD);
	}
	else
	{
		MainHUD->SetVisibility(ESlateVisibility::Hidden);
		SetMouseState(false, EInputModeType::E_GameOnly);
	}
}

void AHero::StatusOn()
{
	if (TechniqueComponent->GetHUDVisible()) return;
	if (!MainHUD->CheckHUDsVisibility())
		SetMouseCenter();

	MainHUD->ToggleStatusHUD();

	if (MainHUD->CheckHUDsVisibility())
	{
		MainHUD->SetVisibility(ESlateVisibility::Visible);
		SetMouseState(true, EInputModeType::E_GameAndUIOnly, MainHUD);
	}
	else
	{
		MainHUD->SetVisibility(ESlateVisibility::Hidden);
		SetMouseState(false, EInputModeType::E_GameOnly);
	}
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

	if (!MainHUDClass)
	{
		UE_LOG(HeroLog, Warning, TEXT("MainHUDClass Is NULL!!"));
		return;
	}

	MainHUD = CreateWidget<UMainHUD>(PlayerController, MainHUDClass, "Main HUD");
	MainHUD->AddToViewport();
	InventoryComponent->InitInvenHUD(MainHUD->GetInvenHUD());
	InventoryComponent->InitContextMenu(MainHUD->GetContextMenu());
	MainHUD->GetInvenHUD()->DToggle.BindUFunction(this, "InventoryOn");
	if (!MainHUD->GetEquipHUD()) { UE_LOG(LogTemp, Warning, TEXT("MainHUD : EquipHUD Is NULL !!")); }
	EquipComponent->InitEquipmentHUD(MainHUD->GetEquipHUD());
	MainHUD->GetEquipHUD()->DToggle.BindUFunction(this, "EquipmentOn");
	StatusComponent->InitStatusHUD(MainHUD->GetStatusHUD());
	MainHUD->GetStatusHUD()->DToggle.BindUFunction(this, "StatusOn");

	MainHUD->GetContextMenu()->SetInvenComp(InventoryComponent);
	MainHUD->GetContextMenu()->SetEquipComp(EquipComponent);

	MainHUD->SetVisibility(ESlateVisibility::Hidden);

	UE_LOG(HeroLog, Log, TEXT("Hero InvenHUD Address: %p"), InvenHUD);
	UE_LOG(HeroLog, Log, TEXT("MainHUD InvenHUD: %p"), MainHUD->GetInvenHUD());

	// Interaction
	if (InteractionHUDClass)
	{
		InteractionHUD = CreateWidget<UInteractionHUD>(PlayerController, InteractionHUDClass, "Interaction HUD");
		InteractionHUD->AddToViewport();
		InteractionHUD->SetVisibility(ESlateVisibility::Hidden);
	}
	else 
	{
		UE_LOG(HeroLog, Warning, TEXT("InteractionHUDClass Is NULL !!"));
		return;
	}

	InteractionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnInteractionBeginOverlap);
	InteractionCapsule->OnComponentEndOverlap.AddDynamic(this, &AHero::OnInteractionEndOverlap);

	//
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + FVector(100, 100, 0);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1, 0, 10);

	
	
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
	MAPPING_CLICK(Comp, InputAsset->AvoidAction, AHero::PressedAvoid, AHero::ReleasedAvoid);
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

	// Soul
	Comp->BindAction(InputAsset->SoulBurn, ETriggerEvent::Started, this, &AHero::SoulBurn);

	// Equipment
	Comp->BindAction(InputAsset->EquipmentOn, ETriggerEvent::Started, this, &AHero::EquipmentOn);

	// Statys
	Comp->BindAction(InputAsset->StatusOn, ETriggerEvent::Started, this, &AHero::StatusOn);
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
		FInputModeGameAndUI InputMode;
		if (widget)
		{
			InputMode.SetWidgetToFocus(widget->TakeWidget());
		}
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 마우스를 눌렀을 때 위치가 고정되지 않도록
		InputMode.SetHideCursorDuringCapture(false);
		cont->SetInputMode(InputMode);

		break;
	}
	case EInputModeType::E_UIOnly:
	{
		FInputModeUIOnly InputMode;
		if (widget)
		{
			InputMode.SetWidgetToFocus(widget->TakeWidget());
		}
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

void AHero::SetMouseCenter()
{
	// Set Mouse Position
	int32 x, y;
	PlayerController->GetViewportSize(x, y);
	PlayerController->SetMouseLocation(x / 2, y / 2);
}

void AHero::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AHero::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AHero::DoDashMovement()
{
	ActionComponent->DoDashMovement();
}

void AHero::OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Item
	TObjectPtr<ABaseItem> Item = Cast<ABaseItem>(OtherComp->GetOwner());

	if (Item && Item->bInField == true)
	{
		OverlapedItems.AddUnique(Item);

		UE_LOG(LogTemp, Log, TEXT("OverlapedItems Num : %d"), OverlapedItems.Num());

		InteractionItem = Item;
		InteractionHUD->SetName(InteractionItem->Name);

		if (InteractionHUD->GetVisibility() == ESlateVisibility::Hidden)
			InteractionHUD->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	// Prob
	TObjectPtr<ABaseProb> Prob = Cast<ABaseProb>(OtherComp->GetOwner());

	if (Prob && !InteractionProb)
	{
		InteractionProb = Prob;
	}
}

void AHero::OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Item
	TObjectPtr<ABaseItem> Item = Cast<ABaseItem>(OtherComp->GetOwner());

	if (Item)
	{
		if (OverlapedItems.Contains(Item))
			OverlapedItems.RemoveAt(OverlapedItems.Find(Item));

		if (InteractionItem == Item)
		{
			InteractionItem = nullptr;

			if (OverlapedItems.Num() == 0)
			{
				InteractionHUD->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				InteractionItem = OverlapedItems[OverlapedItems.Num() - 1];
				InteractionHUD->SetName(InteractionItem->Name);
			}
		}
		else
		{
			if (OverlapedItems.Num() == 0)
			{
				InteractionHUD->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}

	// Prob
	TObjectPtr<ABaseProb> Prob = Cast<ABaseProb>(OtherComp->GetOwner());

	if (Prob)
	{
		if (InteractionProb == Prob)
		{
			InteractionProb = nullptr;
		}
	}




	//if (InteractionItem == nullptr)
	//{
	//	if (OverlapedItems.Num() == 0)
	//	{
	//		InteractionHUD->SetVisibility(ESlateVisibility::Hidden);
	//	}
	//	else
	//	{
	//		InteractionItem = OverlapedItems[OverlapedItems.Num() - 1];
	//		InteractionHUD->SetName(InteractionItem->Name);
	//	}
	//}
	//else
	//{
	//	TObjectPtr<ABaseItem> Item = Cast<ABaseItem>(OtherComp->GetOwner());
	//	OverlapedItems.RemoveAt(OverlapedItems.Find(Item));

	//	if (InteractionItem == Item)
	//	{
	//		if (OverlapedItems.Num() == 0)
	//		{
	//			InteractionItem = nullptr;
	//			InteractionHUD->SetVisibility(ESlateVisibility::Hidden);
	//		}
	//		else
	//		{
	//			//InteractionItem = OverlapedItems[OverlapedItems.Num() - 1];
	//			//InteractionHUD->SetName(InteractionItem->Name);
	//		}
	//	}
	//}
}


void AHero::InitState()
{
	SetCanMove(true);
	SetCanAttack(true);
	SetCurrentState(EStateType::E_Idle);
}

void AHero::SetCurrentWeaponType(EWeaponType type)
{
	Super::SetCurrentWeaponType(type);

	TechniqueComponent->SetCurrentWeaponType(type);
	ActionComponent->SetCurrentWeaponType(type);
}

void AHero::OneMinuteTimePass()
{
	Super::OneMinuteTimePass();
}
