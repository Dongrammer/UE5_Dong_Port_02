#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"

DEFINE_LOG_CATEGORY(HmNPCAIContLog);

AHumanNPC_AIController::AHumanNPC_AIController()
{
}

void AHumanNPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TObjectPtr<AHumanNPC> const npc = Cast<AHumanNPC>(InPawn);
	
	if (!npc)
	{
		UE_LOG(HmNPCAIContLog, Warning, TEXT("%s : Casting AHumanNPC Fail !!"), *InPawn->GetFName().ToString());
		return;
	}

	TObjectPtr<UBehaviorTree> const tree = npc->GetBehaviorTree();

	if (!tree)
	{
		UE_LOG(HmNPCAIContLog, Warning, TEXT("%s : Get BehaviorTree Fail !!"), *InPawn->GetFName().ToString());
		return;
	}

	UBlackboardComponent* bboard = nullptr;
	UseBlackboard(tree->BlackboardAsset, bboard);
	Blackboard = bboard;
	RunBehaviorTree(tree);
}
