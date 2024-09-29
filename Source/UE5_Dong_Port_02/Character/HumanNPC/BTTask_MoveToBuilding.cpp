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

	if (!npc->GetCanMove())
		return EBTNodeResult::Failed;

	//TObjectPtr<ABuilding> building = Cast<ABuilding>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetBuilding"));
	TObjectPtr<ABuilding> building = Cast<ABuilding>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (!building)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveToBuilding : Casting ABuilding Fail !!"));
		return EBTNodeResult::Failed;
	}

	FVector loc = building->GetInDoorLocation();
	EPathFollowingRequestResult::Type t = OwnerComp.GetAIOwner()->MoveToLocation(loc);

	if (t == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_MoveToBuilding::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	TObjectPtr<AAIController> cont = OwnerComp.GetAIOwner();
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveToBuilding : npc Is NULL !!"));
		return;
	}

	if (!npc->GetCanMove())
	{
		cont->StopMovement();
	}

	return;
}
