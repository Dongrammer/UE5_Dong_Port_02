#include "Character/HumanNPC/Hobby/BTDecorator_CheckHobby.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckHobby::UBTDecorator_CheckHobby()
{
	NodeName = TEXT("Check Hobby");
}

bool UBTDecorator_CheckHobby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());

	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckHobby : NPC Is NULL !!"));
		return false;
	}

	result = (checkNPCHobby == npc->GetCurrentHobby());

	return result;
}
