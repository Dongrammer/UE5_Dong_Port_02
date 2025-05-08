#include "Character/HumanNPC/Fight/BTD_CheckFighting.h"
#include "AIController.h"
#include "Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_CheckFighting::UBTD_CheckFighting()
{
	NodeName = TEXT("Check Fighting");
}

bool UBTD_CheckFighting::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	TObjectPtr<ABaseCharacter> character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (!character)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTD_CheckFighting : Character Is NULL !!"));
		return false;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Enemy"), character->GetFighttingCharacter());

	return character->GetFighting();
}
