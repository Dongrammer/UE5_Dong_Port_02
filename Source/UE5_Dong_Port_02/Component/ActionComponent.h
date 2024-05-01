// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action/ActionData.h"
#include "../Weapon/WeaponData.h"

#include "ActionComponent.generated.h"

class AHero;
class ABaseAction;
class UActionDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();
	void SetOwner(AHero* hero);
	
private:
	AHero* Owner;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SettingActions(TArray<TSubclassOf<ABaseAction>> actions);
	void CreateActions();

	UFUNCTION()
	void DoAction();
	UFUNCTION()
	void EndAction();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TArray<TObjectPtr<ABaseAction>> SelectActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UActionDataAsset> ActionDataAsset;

	UPROPERTY()
	TMap<EGauntletAction, TObjectPtr<ABaseAction>> GauntletActionPtr;
	UPROPERTY()
	TMap<ESwordAction, TObjectPtr<ABaseAction>> SwordActionPtr;
};
