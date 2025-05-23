#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Weapon/WeaponData.h"
#include "../Item/ItemData.h"
#include "ActionData.h"

DECLARE_LOG_CATEGORY_EXTERN(ActionLog, Log, All);

#include "BaseAction.generated.h"

class AHero;
class UAnimMontage;

UCLASS()
class UE5_DONG_PORT_02_API ABaseAction : public AActor
{
	GENERATED_BODY()

public:
	ABaseAction();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AHero> ActionOwner;

public:
	virtual void Tick(float DeltaTime) override;

	void SettingOwner(TObjectPtr<AHero> InOwner);

public:
	void DoAction();
	void EndAction();
	UFUNCTION(BlueprintCallable)
	void SetLocation();
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoActionMovement();

	/* ========== Action Information ========== */
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	EWeaponType ActionType;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TSubclassOf<ABaseAction> ActionClass;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TObjectPtr<UAnimMontage> AnimAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> ActionImage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	bool bCanMove = true;
	//UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	//EActiveCollisionType ActiveCollisionType = EActiveCollisionType::E_None;
	/* ========== Action Status ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Status")
	float DamageRate = 100.0f;
	
public:
	FORCEINLINE float GetDamageRate() { return DamageRate; }
	//FORCEINLINE EActiveCollisionType GetActiveCollisionType() { return ActiveCollisionType; }

	/* ========== Action Elements ========== */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 ActionLevel = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential")
	float MoveDistance = 0;
	// For ActionMovement 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FVector StartLocation;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FVector EndLocation;

public:
	FORCEINLINE EWeaponType GetActionType() { return ActionType; }
	FORCEINLINE bool GetCanMove() { return bCanMove; }

	/* ========== Passive ========== */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential")
	TMap<uint8, float> SpeedLevelData; // <노드레벨, 재생속도>
	uint8 SpeedLevel = 0;
	float PlayRate = 1.0f;
	void PassiveSpeedUp();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential")
	TMap<uint8, float> DamageLevelData; // <노드레벨, 데미지 계수>
	uint8 DamageLevel = 0;
	void PassiveDamageUp();

};
