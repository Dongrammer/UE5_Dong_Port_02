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
// Technique
class UTechniqueComponent;
// Action
class UActionComponent;
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

	/* ==================== HUD ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMainHUD> MainHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMainHUD> MainHUDClass;


	/* ==================== Inventory ==================== */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UInventoryHUD> InvenHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryHUD> InvenHUDClass;

private:
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	/* ==================== Technique ==================== */
private:
	UPROPERTY(VisibleAnywhere)
	UTechniqueComponent* TechniqueComponent;

	/* ==================== Action ==================== */
private:
	UPROPERTY(VisibleAnywhere)
	UActionComponent* ActionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanActionMove = true;

public:
	UFUNCTION()
	void DoDashMovement();
	FORCEINLINE UActionComponent* GetActionComponent() { return ActionComponent; }

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

	/* ==================== State ==================== */
public:
	UFUNCTION(BlueprintCallable)
	bool CurrentStateAre(TArray<EStateType> states) { return StatusComponent->CurrentStateAre(states); }
	UFUNCTION(BlueprintCallable)
	bool CurrentStateIs(EStateType state) { return StatusComponent->CurrentStateIs(state); }
	void SetCurrentState(EStateType state) { StatusComponent->SetCurrentState(state); }
	FORCEINLINE EStateType GetCurrentState() { return StatusComponent->GetCurrentState(); }
	void InitState();

	/* ==================== Soul ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoulComponent> SoulComponent;

	/* ==================== Status ==================== */


	/* ==================== Weapon ==================== */
public:
	FORCEINLINE EWeaponType GetCurrentWeaponType() { return WeaponComponent->GetCurrentWeaponType(); }

	void SetCurrentWeaponType(EWeaponType type) override;

	/* ==================== Time ==================== */
public:
	void OneMinuteTimePass() override;
	UFUNCTION(BlueprintCallable)
	void SetTimeMult(float f) { GameInstance->SetTimeMult(f); }
};

/*
	State
	일단 만들고, 나중에 필요하면 컴포넌트로 분리
*/