#include "Character/HumanNPC/BTService_CheckRoutine.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "TPS_GameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckRoutine::UBTService_CheckRoutine()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Check Routines And SetHome");

}

void UBTService_CheckRoutine::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	// Get Home Location
	FVector HomeLocation = npc->GetHomeLocation(); // ������ �� ��ġ�� ������ ������µ�, ���߿� ���� ���� ���� �� �������� ����.

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("HomeLocation", HomeLocation);
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

	uint8 CheckH = 0;
	uint8 CheckM = 0;

	for (auto rou : routines)
	{
		// ������ ���ϰ� ���� ������ ���� �ʴ´ٸ� �ش� ��ƾ�� �������� ����.
		if (!(time.CurrentWeek == EWeekType::E_None))
		{
			if (time.CurrentWeek == rou.Value.CurrentWeek)
				continue;
		}

		if ((rou.Value.CurrentHour == time.CurrentHour) && (rou.Value.CurrentMinute <= time.CurrentMinute))
		{
			if ((CheckH <= rou.Value.CurrentHour) && (CheckM <= rou.Value.CurrentMinute))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), static_cast<uint8>(rou.Key));
				CheckH = rou.Value.CurrentHour;
				CheckM = rou.Value.CurrentMinute;
			}
		}
	}
}
