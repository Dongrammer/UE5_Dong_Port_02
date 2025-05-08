#pragma once

#include "CoreMinimal.h"
#include "Land/Building/Building.h"
#include "Inn.generated.h"

class ADrinkingZone;
class ABaseProb;

UCLASS()
class UE5_DONG_PORT_02_API AInn : public ABuilding
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<TObjectPtr<ADrinkingZone>> DrinkingZones;

public:
	TObjectPtr<ABaseProb> GetValidDrinkingZone() const;
};
