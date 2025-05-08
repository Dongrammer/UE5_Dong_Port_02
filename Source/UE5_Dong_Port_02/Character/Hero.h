#pragma once

#include "CoreMinimal.h"
#include "Character/BaseHuman.h"
#include "Logging/LogMacros.h"
#include "../TPS_GameInstance.h"

DECLARE_LOG_CATEGORY_EXTERN(HeroLog, Log, All);

#include "Hero.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UEnhancedInputComponent;
//class UInputAction;
class UInputDataAsset;
struct FInputActionValue;
// Inventory
// Widget
class UMainHUD;
class UInventoryHUD;
class UWidget;
class UInteractionHUD;
class UShopHUD;
class UDamageFloating;
// Technique
class UTechniqueComponent;
// Soul
class USoulComponent;
//
class ABaseItem;

UENUM()
enum class EInputModeType : uint8
{
	E_GameOnly,
	E_GameAndUIOnly,
	E_UIOnly
};

UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	E_Forward UMETA(DisplayName = "Forward"),
	E_Right UMETA(DisplayName = "Right"),
	E_Left UMETA(DisplayName = "Left"),
	E_Back UMETA(DisplayName = "Back")
};


/*
	[Key Mapping Context], [InputAsset] Direct Specification required.
*/
UCLASS()
class UE5_DONG_PORT_02_API AHero : public ABaseHuman
{
	GENERATED_BODY()

private:
	TObjectPtr<APlayerController> PlayerController;

public:
	AHero();
	void Tick(float DeltaSecond) override;
	FORCEINLINE APlayerController* GetPlayerController() { return PlayerController; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* InteractionCapsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Essential", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Essential", meta = (AllowPrivateAccesss = "true"))
	UInputDataAsset* InputAsset;

public:

protected:
	void BeginPlay() override;
	void CreateCharacter() override;
	void CreateCamera();

	/* ==================== Input ==================== */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	EInputDirection inputDirection = EInputDirection::E_Forward;

protected:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MappingInputAsset(UEnhancedInputComponent* Comp);

public:
	void SetMouseState(bool visibility, EInputModeType inputmode, UWidget* widget = nullptr); // Setting Mouse Visibility, InputMode
	void SetMouseCenter();
	FORCEINLINE EInputDirection GetInputDirection() { return inputDirection; }

public:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void DoInteraction();
	void EndInteraction();

	void WeaponStartUp();

	void DoMainAction();
	void EndMainAction();
	void DoSubAction();
	void EndSubAction();

	void PressedAvoid();
	void ReleasedAvoid();

	UFUNCTION()
	void InventoryOn();
	void QuickSlotWheel();

	void TechniqueOn();
	void EquipWeapon();

	void SoulBurn();

	UFUNCTION()
	void EquipmentOn();

	UFUNCTION()
	void StatusOn();
	UFUNCTION()
	void ShopHUDOn();
	/* ==================== HUD ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMainHUD> MainHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMainHUD> MainHUDClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UShopHUD> ShopHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UShopHUD> ShopHUDClass;


	/* ==================== Inventory ==================== */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UInventoryHUD> InvenHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryHUD> InvenHUDClass;

	void GetGold(int val) override;
	int GetCurrentGold() { return InventoryComponent->GetCurrentGold(); }
	void ItemUse(FItemData data) { InventoryComponent->ItemUse(data); }
	bool CheckCanGetItem(FItemData data);

private:
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/* ==================== Technique ==================== */
private:
	UPROPERTY(VisibleAnywhere)
	UTechniqueComponent* TechniqueComponent;

	/* ==================== Interaction ==================== */
private:
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TObjectPtr<UInteractionHUD> InteractionHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction|Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInteractionHUD> InteractionHUDClass;
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TArray<TObjectPtr<ABaseItem>> OverlapedItems;


	UFUNCTION()
	void OnInteractionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	bool bLeftClicked = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ABaseItem> InteractionItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ABaseProb> InteractionProb;

	/* ==================== Soul ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoulComponent> SoulComponent;

	/* ==================== Status ==================== */

	/* ==================== Action ==================== */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActionComponent> ActionComponent;
public:
	void DoDashMovement() override;
	FORCEINLINE UActionComponent* GetActionComponent() { return ActionComponent; }
	int CalculationDamage(int characterATK) override;
	void EndActionNotify() override;

	/* ==================== Weapon ==================== */
public:
	FORCEINLINE EWeaponType GetCurrentWeaponType() { return WeaponComponent->GetCurrentWeaponType(); }

	void SetCurrentWeapon(TObjectPtr<ABaseWeapon> weapon) override;

	/* ==================== Time ==================== */
public:
	void OneMinuteTimePass() override;
	UFUNCTION(BlueprintCallable)
	void SetTimeMult(float f) { GameInstance->SetTimeMult(f); }

	/* ==================== Widget ==================== */
public:
	virtual void HealthBarVisible() override;
};

/*
	State
	일단 만들고, 나중에 필요하면 컴포넌트로 분리
*/