#include "Character/HumanNPC/Fight/BTT_RunAway.h"

UBTT_RunAway::UBTT_RunAway()
{
	NodeName = TEXT("Run Away from Enemy");
}

EBTNodeResult::Type UBTT_RunAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}
