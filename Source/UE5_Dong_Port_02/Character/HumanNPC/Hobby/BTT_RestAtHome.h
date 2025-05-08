#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RestAtHome.generated.h"

class AHumanNPC_AIController;
class AHumanNPC;
class ABaseProb;
class ABuilding;
class UBlackboardComponent;

struct TaskMemoryRestAtHome
{
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AHumanNPC_AIController> cont;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AHumanNPC> npc;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ABuilding> home;

	int RandomInt = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector TargetLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ABaseProb> prob;

	FTimerHandle timerhandle;
};

UCLASS()
class UE5_DONG_PORT_02_API UBTT_RestAtHome : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTT_RestAtHome();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override;

	UFUNCTION()
	void ChangeAction(UBlackboardComponent* blackboard);
	//void ChangeAction(TaskMemoryRestAtHome* Mem);
};
