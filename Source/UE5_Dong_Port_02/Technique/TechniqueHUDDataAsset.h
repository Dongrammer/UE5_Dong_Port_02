#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "../Weapon/WeaponData.h"

#include "TechniqueHUDDataAsset.generated.h"

class UTechniqueHUD;

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueHUDDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TMap<EWeaponType, TSubclassOf<UTechniqueHUD>> HUDs;
};
