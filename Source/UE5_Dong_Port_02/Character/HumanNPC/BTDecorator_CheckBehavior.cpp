#include "Character/HumanNPC/BTDecorator_CheckBehavior.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"

UBTDecorator_CheckBehavior::UBTDecorator_CheckBehavior()
{
	NodeName = TEXT("Check BehaviorType");
}

bool UBTDecorator_CheckBehavior::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());

	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckBehaviorType : NPC Is NULL !!"));
		return false;
	}

	return npc->CheckBehavior(CheckType);
}
