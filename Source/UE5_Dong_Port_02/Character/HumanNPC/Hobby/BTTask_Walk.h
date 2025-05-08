#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Walk.generated.h"

//class AHumanNPC_AIController;
//class AHumanNPC;
//class ABaseVillage;

//struct FTaskWalkNodeMemory
//{
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
//	TObjectPtr<AHumanNPC_AIController> cont;
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
//	TObjectPtr<AHumanNPC> npc;
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
//	TObjectPtr<ABaseVillage> village;
//};

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_Walk : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	UBTTask_Walk();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
