#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TakeARest.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_TakeARest : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_TakeARest();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>> RestAnims;
};
