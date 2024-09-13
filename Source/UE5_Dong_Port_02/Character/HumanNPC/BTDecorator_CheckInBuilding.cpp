#include "Character/HumanNPC/BTDecorator_CheckInBuilding.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"

UBTDecorator_CheckInBuilding::UBTDecorator_CheckInBuilding()
{
	NodeName = TEXT("Check In Building");
}

bool UBTDecorator_CheckInBuilding::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());

	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckInBuilding : NPC Is NULL !!"));
		return false;
	}

	return npc->IsInBuilding();
}
