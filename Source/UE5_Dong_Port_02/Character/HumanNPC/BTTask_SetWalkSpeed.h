#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetWalkSpeed.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_SetWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_SetWalkSpeed();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Speed;
};
