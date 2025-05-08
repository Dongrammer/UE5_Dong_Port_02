#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Component/WeaponComponent.h"
#include "../Component/ActionComponent.h"
#include "Component/InventoryComponent.h"
#include "../Item/ItemData.h"
#include "../Action/LifeAnimDataAsset.h"
#include "HittedAnimAsset.h"
#include "../Item/BaseWeapon.h"

#include "BaseHuman.generated.h"

class UEquipComponent;
class AHero;
class ABuilding;
class ABaseProb;

UENUM(BlueprintType)
enum class EHandleType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_OneHand UMETA(DisplayName = "One Hand"),
	E_TwoHand UMETA(DisplayName = "Two Hand"),
	E_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class ESittingType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Normal UMETA(DisplayName = "Normal"),
	E_Max UMETA(DisplayName = "Max")
};


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
	virtual void SetCurrentWeapon(TObjectPtr<ABaseWeapon> weapon);

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

public:
	FORCEINLINE AHero* GetHero() { return hero; }

	UFUNCTION()
	virtual void Pushed(FVector direction, float force);

	/* ========== State ========== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	EHandleType CurrentHandle = EHandleType::E_None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	ESittingType CurrentSitting = ESittingType::E_None;

public:
	void SetCurrentHandleType(EHandleType type) { CurrentHandle = type; }
	void SetCurrentSittingType(ESittingType type) { CurrentSitting = type; }

public:
	FORCEINLINE EHandleType GetCurrentHandleType() const { return CurrentHandle; }
	FORCEINLINE ESittingType GetCurrentSittingType() const { return CurrentSitting; }

	/* ========== Inventory ========== */
	UFUNCTION()
	virtual void GetGold(int val);
	UFUNCTION()
	virtual TArray<FItem> GetHaveItems() { return InventoryComponent->GetHaveItems(); }

	/* ========== Hitted ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hitted|Essential")
	TObjectPtr<UHittedAnimAsset> HittedAnim;
public:
	UFUNCTION()
	void PlayPushedAnim(EPushedDirection dir, EPushType type);
	UFUNCTION()
	void PlayHittedAnim(EHumanHittedPoint dir);
	UFUNCTION()
	void PlayDeadAnim(EHumanHittedPoint dir);

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


	/* ==================== Action ==================== */
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanActionMove = true;

public:
	UFUNCTION()
	virtual void DoDashMovement();
	UFUNCTION()
	virtual void EndActionNotify();

	/* ========== Fighting Collision ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RightHandCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> LeftHandCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> RightLegCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> LeftLegCollision;

	TArray<TObjectPtr<UCapsuleComponent>> Collisions;
	TArray<TObjectPtr<ABaseCharacter>> HittedCharacter;
public:
	UFUNCTION()
	void ActiveAttackCollision(EActiveCollisionType collisiontype);
	UFUNCTION()
	void DeactiveAttackCollision();

	UFUNCTION()
	virtual void AttackCollisionOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void TakeDamageFuc(AActor* damagecauser, int damage, FVector hittedlocation) override;
	virtual int CalculationDamage(int characterATK);
	/* ========== Hitted Points ========== */
protected:
	//EHumanHittedPoint TakeDamageDirection;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EHumanHittedPoint, TObjectPtr<USceneComponent>> HittedPointMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> HighForwardPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> HighBackPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> HighLeftPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> HighRightPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> MidForwardPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> MidBackPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> MidLeftPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> MidRightPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> LowForwardPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> LowBackPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> LowLeftPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> LowRightPoint;
};
