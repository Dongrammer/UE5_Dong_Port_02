#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
DECLARE_LOG_CATEGORY_EXTERN(HmNPCAIContLog, Log, All);

#include "HumanNPC_AIController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;

UCLASS()
class UE5_DONG_PORT_02_API AHumanNPC_AIController : public AAIController
{
	GENERATED_BODY()

public:
	//explicit AHumanNPC_AIController(FObjectInitializer const& ObjectInitializer);
	AHumanNPC_AIController();


protected:
	virtual void OnPossess(APawn* InPawn) override;

	/* ========== AI Perception ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> AIPerception;

	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

	UFUNCTION()
	void PerceptionUpdate(const TArray<AActor*>& UpdatedActors);
};
