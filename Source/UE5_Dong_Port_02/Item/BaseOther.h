#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "BaseOther.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ABaseOther : public ABaseItem
{
	GENERATED_BODY()

public:
	ABaseOther();
	virtual void BeginPlay() override;
	//virtual void DataTableSetting() override;

public:
	bool bCanUse = false;

	/*UPROPERTY(VisibleAnywhere)
	TMap<EOtherEffect, float> Effect;
	UPROPERTY(VisibleAnywhere)
	float Duration;

	UPROPERTY(VisibleAnywhere)
	UParticleSystem* EffectParticle;*/
};
