#pragma once

#include "CoreMinimal.h"
#include "Character/BaseHuman.h"
#include "Logging/LogMacros.h"

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
// Technique
class UTechniqueComponent;
// Action
class UActionComponent;
// Soul
class USoulComponent;

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

UENUM(BlueprintType)
enum class EStateType : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Avoid UMETA(DisplayName = "Avoid"),
	E_Hitted UMETA(DisplayName = "Hitted"),
	E_Dead UMETA(DisplayName = "Dead")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAcces = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAcces = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAcces = "true"))
	UInputMappingContext* KeyMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
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

	/* ==================== HUD ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMainHUD> MainHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMainHUD> MainHUDClass;


	/* ==================== Inventory ==================== */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UInventoryHUD> InvenHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryHUD> InvenHUDClass;
	
private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
public:
	bool bLeftClicked = false;

	/* ==================== State ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EStateType CurrentState = EStateType::E_Idle;

public:
	UFUNCTION(BlueprintCallable)
	bool CurrentStateAre(TArray<EStateType> states);
	UFUNCTION(BlueprintCallable)
	bool CurrentStateIs(EStateType state);
	void SetCurrentState(EStateType state) { CurrentState = state; }
	FORCEINLINE EStateType GetCurrentState() { return CurrentState; }
	void InitState();

	/* ==================== Soul ==================== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoulComponent> SoulComponent;

	/* ==================== Status ==================== */

};

/*
	State
	일단 만들고, 나중에 필요하면 컴포넌트로 분리
*/