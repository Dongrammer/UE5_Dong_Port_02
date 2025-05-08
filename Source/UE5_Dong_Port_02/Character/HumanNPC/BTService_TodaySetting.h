#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TodaySetting.generated.h"

class AHumanNPC_AIController;
class AHumanNPC;
//class UTPS_GameInstance;

/*
	단 한번만 실행되도록 하고 싶은데 GlobalTime에 의지할 수 없음. CheckRoutine에서 루틴이 바뀔 때 바꿔주도록 설정
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
