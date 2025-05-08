#include "Character/Hero.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Helper.h"
#include "InputDataAsset.h"
#include "../Component/TechniqueComponent.h"
#include "../Component/WeaponComponent.h"
#include "../Component/SoulComponent.h"
#include "../Component/EquipComponent.h"
#include "Item/BaseItem.h"
#include "Widget/MainHUD.h"
// MainHUD만 포함하고 다른 HUD는 MainHUD의 헤더에 포함시킬지 고민.
#include "Widget/Inventory/InventoryHUD.h"
#include "Widget/Inventory/InventoryContextMenu.h"
#include "Widget/Equipment/EquipmentHUD.h"
#include "Widget/InteractionHUD.h"
#include "Widget/Status/StatusHUD.h"
#include "Widget/Shop/ShopHUD.h"
#include "Blueprint/UserWidget.h"
#include "Item/BaseItem.h"
#include "Kismet/GameplayStatics.h" // 월드 행렬을 뷰포트 행렬로 바꾸기 위해 필요
//#include "TPS_GameInstance.h"
#include "../Land/Prob/BaseProb.h"
#include "../Land/Prob/Shop.h"
#include "Widget/Battle/DamageFloating.h"

#include "NavigationSystem.h"

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
	InteractionCapsule->AttachToComponent(CameraArm, FAttachmentTransformRules::KeepRelativeTransform);
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

	const FRotator Rotation = Controller->GetControlRotation();	// ī ޶                   ȸ    
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// ĳ               Y   ȸ    

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
	if (UsingProb)
	{
		UsingProb->Deactive(this);
		return;
	}

	//bInteraction = true;
	if (InteractionItem)
	{
		if (CheckCanGetItem(InteractionItem->itemdata))
		{
			GetItems(InteractionItem->itemdata, 1);
			InteractionItem->Destroy();
		}
		else
		{
			MainHUD->PlayAnimInventoryWeightOverSign();
		}
	}

	if (InteractionProb)
	{
		TObjectPtr<AShop> shop = Cast<AShop>(InteractionProb);
		if (shop)
		{
			ShopHUD->ActiveHUD(InventoryComponent->GetHaveItems(), shop->GetSellingItemData(), shop->GetValueAdjust(), shop->GetItemType());
			ShopHUDOn();
		}
		else if (UsingProb)
		{
			UsingProb->Deactive(this);
		}
		else
		{
			if (InteractionProb->GetUsed())
			{
				TObjectPtr<ABaseCharacter> UsingCha = InteractionProb->GetUsingHuman();
				UsingCha->AddActorLocalOffset(UsingCha->GetActorForwardVector() * -80);
				InteractionProb->Deactive(InteractionProb->GetUsingHuman());
			}
			InteractionProb->Active(this);
		}
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
	if (!bCanMove) return;

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
	if (GetCurrentWeaponType() == EWeaponType::E_None) return;

	if (WeaponComponent->bHolding)
	{
		WeaponComponent->bHolding = false;
		bUseControllerRotationYaw = false;
		ActionComponent->UnequipWeapon();
	}
	else if (!WeaponComponent->bHolding)
	{
		WeaponComponent->bHolding = true;
		bUseControllerRotationYaw = true;
		ActionComponent->EquipWeapon();
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

void AHero::ShopHUDOn()
{
	if (ShopHUD->GetVisibility() == ESlateVisibility::Visible)
	{
		ShopHUD->SetVisibility(ESlateVisibility::Hidden);
		SetMouseState(false, EInputModeType::E_GameOnly);
	}
	else
	{
		ShopHUD->SetVisibility(ESlateVisibility::Visible);
		SetMouseCenter();
		SetMouseState(true, EInputModeType::E_GameAndUIOnly, ShopHUD);
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

	// Shop
	if (!ShopHUDClass)
	{
		UE_LOG(HeroLog, Warning, TEXT("ShopHUDClass Is NULL!!"));
		return;
	}
	ShopHUD = CreateWidget<UShopHUD>(PlayerController, ShopHUDClass, "Shop HUD");
	ShopHUD->AddToViewport();
	ShopHUD->SetVisibility(ESlateVisibility::Hidden);
	ShopHUD->DShopHUDToggle.BindUFunction(this, "ShopHUDOn");
	ShopHUD->SetOwnerPlayer(this);

	for (int i = 0; i < 100; i++)
	{
		UNavigationSystemV1* navsystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		FNavLocation navlocation;
		navsystem->GetRandomPoint(navlocation);
		//DrawDebugLine(GetWorld(), navlocation.Location, navlocation.Location + FVector(0, 0, 1000), FColor::Green, true, -1.0f, 0, 10.0f);
	}
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

void AHero::GetGold(int val)
{
	Super::GetGold(val);

	if (MainHUD->GetInvenHUD()->FGoldUpdate.IsBound())
		MainHUD->GetInvenHUD()->FGoldUpdate.Execute(InventoryComponent->GetCurrentGold());
}

bool AHero::CheckCanGetItem(FItemData data)
{
	return InventoryComponent->CheckCanGetItem(data);
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

int AHero::CalculationDamage(int characterATK)
{
	int damage = characterATK * (ActionComponent->GetNowActionDamageRate() * 0.01f);
	return damage;
}

void AHero::EndActionNotify()
{
	ActionComponent->OnEndActionNotify();
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

		InteractionHUD->ActiveWidget(EInteractionHUDType::E_Get, InteractionItem->Name);
	}

	// Prob
	TObjectPtr<ABaseProb> Prob = Cast<ABaseProb>(OtherComp->GetOwner());

	if (Prob && !InteractionProb)
	{
		// Shop
		TObjectPtr<AShop> shop = Cast<AShop>(Prob);
		if (shop)
		{
			if (shop->GetUsed())
			{
				InteractionProb = Prob;

				InteractionHUD->ActiveWidget(EInteractionHUDType::E_Trade, InteractionProb->GetName());
			}
		}
		// Prob
		else if (Prob->GetCanPlayerUse())
		{
			InteractionProb = Prob;

			InteractionHUD->ActiveWidget(EInteractionHUDType::E_Use, InteractionProb->GetName());
		}
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
				InteractionHUD->DeactiveWidget();
			}
			else
			{
				InteractionItem = OverlapedItems[OverlapedItems.Num() - 1];
				InteractionHUD->ChangeName(InteractionItem->Name);
			}
		}
		else
		{
			if (OverlapedItems.Num() == 0)
			{
				InteractionHUD->DeactiveWidget();
			}
		}
	}


	TObjectPtr<ABaseProb> Prob = Cast<ABaseProb>(OtherComp->GetOwner());
	// Shop
	TObjectPtr<AShop> shop = Cast<AShop>(Prob);
	if (shop)
	{
		if (InteractionProb == shop)
		{
			InteractionProb = nullptr;

			InteractionHUD->DeactiveWidget();
		}
	}
	// Prob
	else if (Prob)
	{
		if (InteractionProb == Prob)
		{
			InteractionProb = nullptr;

			InteractionHUD->DeactiveWidget();
		}
	}
}

void AHero::SetCurrentWeapon(TObjectPtr<ABaseWeapon> weapon)
{
	Super::SetCurrentWeapon(weapon);

	TechniqueComponent->SetCurrentWeaponType(weapon->GetWeaponType());
	ActionComponent->SetCurrentWeaponType(weapon->GetWeaponType());
}

void AHero::OneMinuteTimePass()
{
	Super::OneMinuteTimePass();
}

void AHero::HealthBarVisible()
{
}
