#include "Character/HumanNPC/Hobby/BTTask_Drinking.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Land/BaseVillage.h"
#include "Land/Building/Inn.h"

UBTTask_Drinking::UBTTask_Drinking()
{
	NodeName = TEXT("Drinking");
}

EBTNodeResult::Type UBTTask_Drinking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TaskMemoryDrinking* memory = (TaskMemoryDrinking*)(NodeMemory);
	bool bRandomSet = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bRandomSet"));

	if (bRandomSet == false)
	{
		const TObjectPtr<AHumanNPC_AIController> cont = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());
		if (!cont)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Drinking : NPC Controller Is NULL !!"));
			return EBTNodeResult::Failed;
		}
		const TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
		if (!npc)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Drinking : NPC Is NULL !!"));
			return EBTNodeResult::Failed;
		}
		const TObjectPtr<ABaseVillage> village = npc->GetVillage();
		if (!village)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Drinking : Village Is NULL !!"));
			return EBTNodeResult::Failed;
		}
		const TArray<TObjectPtr<AInn>> inns = village->GetInns();
		if (inns.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Drinking : Inns Num Is 0 !!"));
			return EBTNodeResult::Failed;
		}

		int rand = FMath::RandRange(0, inns.Num() - 1);
		memory->inn = inns[rand];
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bRandomSet"), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetBuilding"), memory->inn);
		if (memory->inn->GetValidDrinkingZone())
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetObject"), memory->inn->GetValidDrinkingZone());
		else // inn is full
		{
			npc->SetRandomHobby();
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("TodayHobby"), static_cast<uint8>(npc->GetCurrentHobby()));
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bRandomSet"), false);
		}

		return EBTNodeResult::Succeeded;
	}

	/*if (memory->npc)
	{
		if (memory->npc->IsInBuilding())
		{
			memory->inn
		}
	}*/

	return EBTNodeResult::Failed;
}

uint16 UBTTask_Drinking::GetInstanceMemorySize() const
{
	return sizeof(TaskMemoryDrinking);
}
