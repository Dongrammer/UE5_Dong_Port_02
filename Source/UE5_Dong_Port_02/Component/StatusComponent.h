#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Character/StatusData.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(StatusCompLog, Log, All);

#include "StatusComponent.generated.h"

class ABaseCharacter;
class UStatusHUD;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

	TObjectPtr<ABaseCharacter> OwnerCharacter;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/* ========== HUD ========== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatusHUD> StatusHUD;

public:
	void InitStatusHUD(TObjectPtr<UStatusHUD> hud);

	/* ========== State ========== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	EStateType CurrentState = EStateType::E_Idle;

public:
	void SetCurrentState(EStateType state) { CurrentState = state; }
	UFUNCTION()
	bool CurrentStateAre(TArray<EStateType> states);
	UFUNCTION()
	bool CurrentStateIs(EStateType state);
	
	FORCEINLINE EStateType GetCurrentState() { return CurrentState; }

	bool CheckDead() { return CurrentStateIs(EStateType::E_Dead); }

	/* ========== EffectState ========== */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	EStateEffectType CurrentEffectState = EStateEffectType::E_None;

public:
	UFUNCTION()
	void SetCurrentEffectState(EStateEffectType type);
	
	FORCEINLINE EStateEffectType GetCurrentEffectState() { return CurrentEffectState; }

	/* ========== Status ========== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FStatus TotalStatus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	FStatus CharacterStatus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	FStatus EquipStatus;

public:
	UFUNCTION()
	void CombineStatus();
	UFUNCTION()
	void InitStatus();
	UFUNCTION()
	void UpdateStatusHUD();	// Only Player
	FStatus GetTotalStatus() { return TotalStatus; }

	UFUNCTION()
	void EquipItemStatus(TMap<EEquipStatus, int> status);
	UFUNCTION()
	void UnequipItemStatus(TMap<EEquipStatus, int> status);


	/* ========== Status ========== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FLifeStatus LifeStatus;


public:
	void UpdateHP(int val);
	void UpdateAttack(int val);

	/* ========== Level ========== */
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	int MaxLevel = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	uint8 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	int Exp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	int UpExp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TArray<int> UpExpList;

public:
	UFUNCTION()
	void GetEXP(int val);

	UFUNCTION()
	void LevelUp();

};
