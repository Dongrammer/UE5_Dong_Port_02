#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

DECLARE_LOG_CATEGORY_EXTERN(EquipComponentLog, Log, All);

#include "EquipComponent.generated.h"

class UEquipmentHUD;
class ABaseHuman;
class ABaseEquip;
class AItemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipComponent();
	TObjectPtr<ABaseHuman> OwnerCharacter;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* ==================== HUD ==================== */ 
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentHUD> EquipmentHUD;

public:
	void ToggleHUD();
	void InitEquipmentHUD(TObjectPtr<UEquipmentHUD> hud);

	/* ==================== Equipment ==================== */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseEquip> Head;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseEquip> Chest;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseEquip> Legs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseEquip> Feet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseEquip> Hands;

public:
	void Equip();
};
