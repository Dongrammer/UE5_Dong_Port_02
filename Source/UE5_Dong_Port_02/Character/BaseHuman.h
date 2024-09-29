#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Component/WeaponComponent.h"
#include "../Item/ItemData.h"
#include "../Action/LifeAnimDataAsset.h"
#include "HittedAnimAsset.h"

#include "BaseHuman.generated.h"

class UInventoryComponent;
class UEquipComponent;
class AHero;
<<<<<<< HEAD
class ABuilding;
class ABaseProb;
=======
>>>>>>> parent of 61cfc84 (~2024/09/14 Update)

UCLASS()
class UE5_DONG_PORT_02_API ABaseHuman : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseHuman();

	bool bInteraction = false;
	UFUNCTION()
	virtual void GetItems(FItemData item, int count);
	virtual bool CheckItemWeight(float itemweight);
	virtual TObjectPtr<UWeaponComponent> GetWeaponComponent() { return WeaponComponent; }
	virtual bool GetWeaponHolding();
	virtual void SetCurrentWeaponType(EWeaponType type);

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter() override;
	virtual void SetCharacterMovement() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponComponent> WeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UEquipComponent> EquipComponent;

protected:
	AHero* hero;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float PlayRate = 1.0f;
	/* PlayRate : BaseAction과 Movement에 영향 */

public:
	void SetPlayRate(float playrate);
	FORCEINLINE float GetPlayRate() { return PlayRate; }

<<<<<<< HEAD
public:
	FORCEINLINE AHero* GetHero() { return hero; }

	UFUNCTION()
	virtual void Pushed(FVector direction, float force);

	/* ========== Hitted ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hitted|Essential")
	TObjectPtr<UHittedAnimAsset> HittedAnim;
public:
	UFUNCTION()
	void PlayHittedAnim(EHittedDirection dir, EHittedType type);

	/* ========== Building ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ABuilding> CurrentBuilding;

public:
	UFUNCTION()
	void SetCurrentBuilding(ABuilding* building) { CurrentBuilding = building; }

	bool IsInBuilding() { return !(CurrentBuilding == nullptr); }
	TObjectPtr<ABuilding> GetCurrentBuilding() { return CurrentBuilding; }

	/* ========== Life Anim ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Life Anim|Essential")
	TObjectPtr<ULifeAnimDataAsset> LifeAnims;

public:
	UFUNCTION()
	void PlayInteractionAnim(EInteractionType type);
	UFUNCTION()
	void PlayWorkAnim(EWorkType type);
	UFUNCTION()
	void PlayRestingAnim(ERestType type);
	UFUNCTION()
	void StopWorkAnim(EWorkType type);
public:
	/* ========== Working ========== */
protected:
	EBehaviorType BehaviorType;
	//bool Working = false;
	TObjectPtr<ABaseProb> UsingProb;

public:
	void SetBehavior(EBehaviorType type) { BehaviorType = type; }
	//void SetWorking(bool b) { SetBehavior; }
	void SetUsingProb(TObjectPtr<ABaseProb> prob) { UsingProb = prob; }
	virtual void StartWork(EWorkType type); // For NPC Fatigue
	virtual void StopWork();

	bool CheckBehavior(EBehaviorType type) { return BehaviorType == type; }
	//bool GetIsWorking() { return BehaviorType == EBehaviorType::E_Working; }
	TObjectPtr<ABaseProb> GetUsingProb() { return UsingProb; }
	EWorkType GetCurrentWorkingType();

	/* ========== Prob ========== */
public:
	TArray<TObjectPtr<ABaseProb>> SphereTraceForBaseProbs(float radius);

=======
>>>>>>> parent of 61cfc84 (~2024/09/14 Update)
};
