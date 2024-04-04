#pragma once

#include "CoreMinimal.h"
#include "Character/BaseHuman.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(HeroLog, Log, All);

#include "Hero.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
//class UInputAction;
class UInputDataAsset;
struct FInputActionValue;
// Inventory
class ABaseItem;
// Widget
class UInventoryHUD;

/*
	[Key Mapping Context], [InputAsset] 직접 지정 필요.
*/
UCLASS()
class UE5_DONG_PORT_02_API AHero : public ABaseHuman
{
	GENERATED_BODY()

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
	AHero();
	void Tick(float DeltaSecond) override;

	void CreateCharacter() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void DoInteraction();
	void EndInteraction();

	void WeaponStartUp();

	void DoMainAction();
	void EndMainAction();
	void DoSubAction();
	void EndSubAction();

	void DoAvoid();
	void EndAvoid();

	void InventoryOn();
	void QuickSlotWheel();


private:

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD")
	TObjectPtr<UInventoryHUD> InvenHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryHUD> InvenHUDClass;
	
protected:
	void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void CreateCamera();
	void MappingInputAsset(UEnhancedInputComponent* Comp);

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
