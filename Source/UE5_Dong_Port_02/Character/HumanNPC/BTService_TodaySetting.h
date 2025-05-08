#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TodaySetting.generated.h"

class AHumanNPC_AIController;
class AHumanNPC;
//class UTPS_GameInstance;

/*
	�� �ѹ��� ����ǵ��� �ϰ� ������ GlobalTime�� ������ �� ����. CheckRoutine���� ��ƾ�� �ٲ� �� �ٲ��ֵ��� ����
*/

struct FTodaySettingNodeMemory
{
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<AHumanNPC_AIController> cont;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<AHumanNPC> npc;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	//TObjectPtr<UTPS_GameInstance> GameInstance;
};

UCLASS()
class UE5_DONG_PORT_02_API UBTService_TodaySetting : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	UBTService_TodaySetting();
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override;
};
