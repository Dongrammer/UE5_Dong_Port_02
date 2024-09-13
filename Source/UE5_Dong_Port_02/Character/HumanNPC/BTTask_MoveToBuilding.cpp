#include "Character/HumanNPC/BTTask_MoveToBuilding.h"
#include "BTTask_MoveToBuilding.h"

#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "../../Land/Building/Building.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_MoveToBuilding::UBTTask_MoveToBuilding()
{
	NodeName = TEXT("Move To Building");
}

EBTNodeResult::Type UBTTask_MoveToBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get NPC
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveToBuilding : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	// Set TargetBuilding // Temp
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), npc->GetHome());

	// 
	TObjectPtr<ABuilding> building = Cast<ABuilding>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetBuilding"));
	if (!building)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveToBuilding : Casting ABuilding Fail !!"));
		return EBTNodeResult::Failed;
	}
	
	//FVector loc = building->GetOutDoorLocation();
	FVector loc = building->GetInDoorLocation();
	EPathFollowingRequestResult::Type t = OwnerComp.GetAIOwner()->MoveToLocation(loc);
	
	if (t == EPathFollowingRequestResult::RequestSuccessful)
	{
		//GetWorld()->GetTimerManager().SetTimer(EndTimer, this, &UBTTask_MoveToBuilding::EndTask, 1.0f, false);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}