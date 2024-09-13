#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckRoutine.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTService_CheckRoutine : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_CheckRoutine();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
