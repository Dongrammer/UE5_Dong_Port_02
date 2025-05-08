#include "Land/Building/Inn.h"
#include "Land/Prob/DrinkingZone.h"

TObjectPtr<ABaseProb> AInn::GetValidDrinkingZone() const
{
	TArray<TObjectPtr<ADrinkingZone>> DZones = DrinkingZones;

	for (int i = 0; i < DZones.Num(); i++)
	{
		int rand = FMath::Rand() % DZones.Num();

		if (!DZones[rand]->GetUsed())
		{
			return DZones[rand];
		}
		else
		{
			DZones.RemoveAt(rand);
		}
	}
	
	return TObjectPtr<ABaseProb>();
}
