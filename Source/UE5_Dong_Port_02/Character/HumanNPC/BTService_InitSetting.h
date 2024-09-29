#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_InitSetting.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTService_InitSetting : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_InitSetting();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
