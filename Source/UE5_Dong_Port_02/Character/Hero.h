#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
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
class UInventoryComponent;
class ABaseItem;

/*
	[Key Mapping Context], [InputAsset] 직접 지정 필요.
*/
UCLASS()
class UE5_DONG_PORT_02_API AHero : public ABaseCharacter
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

	void WeaponStartUp();

	void DoMainAction();
	void EndMainAction();
	void DoSubAction();
	void EndSubAction();

	void DoAvoid();
	void EndAvoid();

	void InventoryOn();
	void QuickSlotWheel();

	UFUNCTION()
	void GetItems(ABaseItem* item, int count);

private:
	UPROPERTY(VisibleAnywhere)
	UInventoryComponent* InventoryComponent;
	TArray<ABaseItem*> Items;

protected:
	void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void CreateCamera();
	void MappingInputAsset(UEnhancedInputComponent* Comp);

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
