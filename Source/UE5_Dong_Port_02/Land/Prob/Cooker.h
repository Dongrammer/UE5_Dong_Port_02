#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "Cooker.generated.h"

class AHumanNPC;

UCLASS()
class UE5_DONG_PORT_02_API ACooker : public ABaseProb
{
	GENERATED_BODY()

public:
	ACooker();

	void Active(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

private:
	TObjectPtr<AHumanNPC> npc;
	FTimerHandle ChangeHandle;
	float ChangeTime = 10.0f;

	UFUNCTION()
	void ChangeHobby();
};
