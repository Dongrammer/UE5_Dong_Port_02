// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action/ActionData.h"
#include "../Weapon/WeaponData.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(ActionCompLog, Log, All);

#include "ActionComponent.generated.h"

class AHero;
class ABaseAction;
class UActionDataAsset;
class ABaseDash;

USTRUCT(BlueprintType)
struct FActionArray
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<ABaseAction>> Actions;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();
	
private:
	AHero* Owner;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* ==================== Action ==================== */
public:
	void SettingActions(TArray<FActionData> actions);
	void CreateActions();
	void PassiveLevelUp(FActionData InAction, EActionPassiveType Ptype);
	void SetCurrentWeaponType(EWeaponType type) { CurrentWeaponType = type; }

	UFUNCTION()
	void DoAction();
	UFUNCTION()
	void EndAction();
	uint8 MontageIndex = 0;
	bool bNextAction = false; // Set true when action is playing

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponType CurrentWeaponType = EWeaponType::E_Gauntlet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TMap<EWeaponType, FActionArray> SelectActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UActionDataAsset> ActionDataAsset;
	UPROPERTY(BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<ABaseAction> NowAction;

	UPROPERTY()
	TMap<EDashAction, TObjectPtr<ABaseDash>> DashActionPtr;
	UPROPERTY()
	TMap<EGauntletAction, TObjectPtr<ABaseAction>> GauntletActionPtr;
	UPROPERTY()
	TMap<ESwordAction, TObjectPtr<ABaseAction>> SwordActionPtr;

	// Get
public:
	FORCEINLINE TObjectPtr<ABaseAction> GetNowAction() { return NowAction; }

	// Notify
public:
	UFUNCTION()
	void OnEndActionNotify();

	/* ==================== Avoid ==================== */
public:
	UFUNCTION()
	void PressedAvoid();
	UFUNCTION()
	void ReleasedAvoid();
	UFUNCTION()
	void DoDashMovement();
	UFUNCTION()
	void OnEndDashNotify();
	UFUNCTION()
	void SettingDashAction(EDashAction dash);

	FORCEINLINE TObjectPtr<ABaseDash> GetDashAction() { return SelectDashAction; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseDash> SelectDashAction;

};
