#include "Character/HumanNPC/BTService_InitSetting.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "Land/Building/Building.h"

UBTService_InitSetting::UBTService_InitSetting()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Init Setting");
}

void UBTService_InitSetting::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Player
	TObjectPtr<AHumanNPC_AIController> cont = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());
	if (!cont)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitSetting : NPC Controller Is NULL !!"));
		return;
	}
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitSetting : NPC Is NULL !!"));
		return;
	}
	/*TObjectPtr<ABuilding> home = npc->GetHome();
	if (!home)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitSetting : Home Is NULL !!"));
		return;
	}*/

	OwnerComp.GetBlackboardComponent()->SetValueAsObject("HomeObject", npc->GetHome());
}
