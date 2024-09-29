#include "Character/HumanNPC/BTDecorator_CheckCondition.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"

UBTDecorator_CheckCondition::UBTDecorator_CheckCondition()
{
	NodeName = TEXT("Check Condition");
}

bool UBTDecorator_CheckCondition::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());

	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckBehaviorType : NPC Is NULL !!"));
		return false;
	}

	bool result = false;

	// Check Fatigue
	if (OverCondition.Contains(EConditionType::E_Fatigue))
	{
		if (npc->GetCurrentFatigue() <= OverCondition.FindRef(EConditionType::E_Fatigue))
		{
			result = true;
		}
	}

	return result;
}
