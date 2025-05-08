#include "Character/HumanNPC/BTService_TodaySetting.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
//#include "TPS_GameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_TodaySetting::UBTService_TodaySetting()
{
	NodeName = TEXT("To Day Setting");
	bNotifyBecomeRelevant = true;
}

void UBTService_TodaySetting::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FTodaySettingNodeMemory* memory = (FTodaySettingNodeMemory*)NodeMemory;

	//FGlobalTime time = memory->GameInstance->GetGlobalTime();

	TObjectPtr<AHumanNPC> npc = memory->npc;

	if (npc->GetCurrentRoutine() == ERoutineType::E_Sleep)
	{
		npc->SetRandomHobby();
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("TodayHobby"), static_cast<uint8>(npc->GetCurrentHobby()));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bRandomSet"), false);
	}
}

void UBTService_TodaySetting::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	FTodaySettingNodeMemory* memory = (FTodaySettingNodeMemory*)NodeMemory;

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

	// Hobby
	npc->SetRandomHobby();
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("TodayHobby"), static_cast<uint8>(npc->GetCurrentHobby()));

	//// Get GameInstance
	//TObjectPtr<UTPS_GameInstance> GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	//if (!GameInstance)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CheckRoutine : GameInstance Is NULL !!"));
	//	return;
	//}

	//memory->GameInstance = GameInstance;
}

uint16 UBTService_TodaySetting::GetInstanceMemorySize() const
{
	return sizeof(FTodaySettingNodeMemory);
}
