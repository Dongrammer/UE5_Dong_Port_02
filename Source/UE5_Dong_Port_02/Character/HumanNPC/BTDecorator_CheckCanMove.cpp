#include "Character/HumanNPC/BTDecorator_CheckCanMove.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"

UBTDecorator_CheckCanMove::UBTDecorator_CheckCanMove()
{
	NodeName = TEXT("Check CanMove");
}

bool UBTDecorator_CheckCanMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());

	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckCanMove : NPC Is NULL !!"));
		return false;
	}

	return npc->GetCanMove();
}
