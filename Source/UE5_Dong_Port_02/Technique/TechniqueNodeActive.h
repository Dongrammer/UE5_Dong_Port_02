#pragma once

#include "CoreMinimal.h"
#include "Technique/TechniqueNodeBase.h"

#include "../Action/ActionData.h"

#include "TechniqueNodeActive.generated.h"

UCLASS(BlueprintType)
class UE5_DONG_PORT_02_API UTechniqueNodeActive : public UTechniqueNodeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FActionData Action;

public:
	FActionData GetAction() { return Action; }
};
