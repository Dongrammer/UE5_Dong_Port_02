#pragma once

#include "CoreMinimal.h"
#include "Technique/TechniqueNodeBase.h"

#include "../Action/ActionData.h"

#include "TechniqueNodePassive.generated.h"

UCLASS(BlueprintType)
class UE5_DONG_PORT_02_API UTechniqueNodePassive : public UTechniqueNodeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EActionPassiveType PassiveType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FActionData TargetAction;
};
