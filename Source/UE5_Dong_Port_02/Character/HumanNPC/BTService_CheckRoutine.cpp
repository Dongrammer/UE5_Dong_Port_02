#include "Character/HumanNPC/BTService_CheckRoutine.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "TPS_GameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Land/BaseVillage.h"

UBTService_CheckRoutine::UBTService_CheckRoutine()
{
	NodeName = TEXT("Check Routines And SetHome");
	bNotifyBecomeRelevant = true;
}

void UBTService_CheckRoutine::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FNPCNodeMemory* memory = (FNPCNodeMemory*)NodeMemory;

	// Temp
	TObjectPtr<AHumanNPC> npc = memory->npc;
	if (npc->CheckOverFatique() && npc->CheckBehavior(EBehaviorType::E_Working))
	{
		npc->SetBehavior(EBehaviorType::E_Resting);
		if (npc->GetUsingProb())
			npc->GetUsingProb()->Deactive(npc);
	}

	if (npc->GetCurrentFatigue() <= 0 && (npc->GetCurrentRoutine() == ERoutineType::E_GoWork) && npc->CheckBehavior(EBehaviorType::E_Resting))
	{
		npc->SetBehavior(EBehaviorType::E_None);
		if (npc->GetUsingProb())
		{
			UE_LOG(LogTemp, Log, TEXT("CheckRoutine : Temp Deactive Call"));
			npc->GetUsingProb()->Deactive(npc);
		}
	}

	// Get Time
	FGlobalTime time = memory->GameInstance->GetGlobalTime();

	// Check Routine
	ERoutineType BeforeRoutine = npc->GetCurrentRoutine();
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
			ERoutineType PrevRoutine = npc->GetCurrentRoutine();

			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<uint8>(rou.Key));
			npc->SetCurrentRoutine(rou.Key);

			if (npc->GetUsingProb() && (npc->GetCurrentRoutine() != PrevRoutine))
			{
				npc->GetUsingProb()->Deactive(npc);
			}

			break;
		}
	}
	ERoutineType AfterRoutine = npc->GetCurrentRoutine();

	// Init Setting per Routines
	if (BeforeRoutine != AfterRoutine)
	{
		if (npc->GetCurrentRoutine() == ERoutineType::E_DoHobby)
		{
			npc->SetRandomHobby();
			OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("TodayHobby"), static_cast<uint8>(npc->GetCurrentHobby()));
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), npc->GetVillage()->GetRandomLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bRandomSet"), false);
		}
	}

	return;
}

void UBTService_CheckRoutine::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	FNPCNodeMemory* memory = (FNPCNodeMemory*)NodeMemory;

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

	memory->cont = cont;
	memory->npc = npc;

	// Get GameInstance
	TObjectPtr<UTPS_GameInstance> GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("CheckRoutine : GameInstance Is NULL !!"));
		return;
	}

	memory->GameInstance = GameInstance;
}

uint16 UBTService_CheckRoutine::GetInstanceMemorySize() const
{
	return sizeof(FNPCNodeMemory);
}
