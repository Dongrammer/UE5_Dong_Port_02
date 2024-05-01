#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "../Action/ActionData.h"

#include "ActionDataAsset.generated.h"

class ABaseAction;

UCLASS()
class UE5_DONG_PORT_02_API UActionDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "Gauntlet")
	TMap<EGauntletAction, TSubclassOf<ABaseAction>> Gauntlet_Actions;
	
	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "Sword")
	TMap<ESwordAction, TSubclassOf<ABaseAction>> Sword_Actions;
};
