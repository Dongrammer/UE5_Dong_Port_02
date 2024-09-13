#include "Character/HumanNPC/BTDecorator_CheckRoutine.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckRoutine::UBTDecorator_CheckRoutine()
{
	NodeName = TEXT("Check Routines");
}

bool UBTDecorator_CheckRoutine::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool Result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	// Get Blackboard Component
	const TObjectPtr<UBlackboardComponent> BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTDecorator_CheckRoutine : Blackboard Comp Is NULL !!"));
		return false;
	}

	ERoutineType RoutineType = (ERoutineType)BlackboardComp->GetValueAsEnum(RoutineKey.SelectedKeyName);

	if (RoutineType == RequireCheckRoutine)
		return true;
	else
		return false;
}
