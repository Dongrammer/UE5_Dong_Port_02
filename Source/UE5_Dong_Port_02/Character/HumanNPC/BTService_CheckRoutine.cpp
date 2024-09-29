#include "Character/HumanNPC/BTService_CheckRoutine.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "TPS_GameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckRoutine::UBTService_CheckRoutine()
{
	NodeName = TEXT("Check Routines And SetHome");
}

void UBTService_CheckRoutine::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get Player
	TObjectPtr<AHumanNPC_AIController> cont = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());
	if (!cont)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckRoutine : NPC Controller Is NULL !!"));
		return;
	}
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckRoutine : NPC Is NULL !!"));
		return;
	}

	// Temp
	if (npc->CheckOverFatique() && npc->CheckBehavior(EBehaviorType::E_Working))
	{
		npc->SetBehavior(EBehaviorType::E_Resting);
		if (npc->GetUsingProb())
			npc->GetUsingProb()->Deactive(npc);
	}
	if (npc->GetCurrentFatigue() <= 0 && (npc->GetCurrentRoutine() == ERoutineType::E_GoWork))
	{
		npc->SetBehavior(EBehaviorType::E_None);
		if (npc->GetUsingProb())
			npc->GetUsingProb()->Deactive(npc);
	}

	// Get Time
	TObjectPtr<UTPS_GameInstance> GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckRoutine : GameInstance Is NULL !!"));
		return;
	}
	FGlobalTime time = GameInstance->GetGlobalTime();

	// Check Routine
	TMap<ERoutineType, FGlobalTime> routines = npc->GetRoutines();

	for (auto rou : routines) // 루틴이 내림차순으로 정렬되어있음.
	{
		// 지정한 요일과 현재 요일이 맞지 않는다면 해당 루틴을 실행하지 않음.
		if (!(time.CurrentWeek == EWeekType::E_None))
		{
			if (time.CurrentWeek == rou.Value.CurrentWeek)
				continue;
		}

		if (rou.Value.CurrentTime <= time.CurrentTime)
		{
			if (npc->GetUsingProb() && (npc->GetCurrentRoutine() != rou.Key))
			{
				npc->GetUsingProb()->Deactive(npc);
			}

			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<uint8>(rou.Key));
			npc->SetCurrentRoutine(rou.Key);
			return;
		}
	}
}
