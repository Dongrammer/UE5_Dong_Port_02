#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "Character/HumanNPC.h"

#include "BTDecorator_CheckRoutine.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTDecorator_CheckRoutine : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

protected:
	UBTDecorator_CheckRoutine();
	//virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
//
//
//protected:
//	UPROPERTY(EditAnywhere, Category = "Blackboard")
//	FBlackboardKeySelector RoutineKey;
//
//	UPROPERTY(EditAnywhere, Category = "Blackboard")
//	ERoutineType RequireCheckRoutine;
};
