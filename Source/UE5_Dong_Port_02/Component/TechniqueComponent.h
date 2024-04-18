#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Weapon/WeaponData.h"
#include "../Action/ActionData.h"

DECLARE_LOG_CATEGORY_EXTERN(TechniqueComponentLog, Log, All);

#include "TechniqueComponent.generated.h"

class AHero;
class UTechniqueHUDDataAsset;
class UTechniqueHUD;
class UBaseAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UTechniqueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTechniqueComponent();

	void ToggleHUD();

	void ApplyAction();

protected:
	virtual void BeginPlay() override;

	EWeaponType CurrentWeaponType;
	TObjectPtr<AHero> Player;
	TObjectPtr<APlayerController> PlayerController;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueHUDDataAsset> TechniqueHUDDataAsset;
	UPROPERTY()
	TObjectPtr<UTechniqueHUD> Gauntlet_TechniqueHUD;
	UPROPERTY()
	TObjectPtr<UTechniqueHUD> Sword_TechniqueHUD;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UBaseAction>> AvailableAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UBaseAction>> SelectedAction;
};
