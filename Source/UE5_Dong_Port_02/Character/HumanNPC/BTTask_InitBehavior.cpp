#include "Character/HumanNPC/BTTask_InitBehavior.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "Land/Prob/BaseProb.h"

UBTTask_InitBehavior::UBTTask_InitBehavior()
{
}

EBTNodeResult::Type UBTTask_InitBehavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get NPC
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_InitBehavior : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	npc->GetUsingProb()->Deactive(npc);
	npc->InitCondition();

	return EBTNodeResult::Succeeded;
}
