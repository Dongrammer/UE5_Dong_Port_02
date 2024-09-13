#include "Character/HumanNPC/BTTask_FindRandomLocation.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "Find Random Location Node";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Controller
	TObjectPtr<AHumanNPC_AIController> const OwnerController = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());

	if (!OwnerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindRandomLocation : OwnerController Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	// Get NPC
	TObjectPtr<APawn> const npc = OwnerController->GetPawn();

	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindRandomLocation : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	// Get NavSystem
	TObjectPtr<UNavigationSystemV1> NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!NavSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("FindRandomLocation : NavSystem Is NULL !!"));
		return EBTNodeResult::Failed;
	}
	
	// Set Location
	FVector const Origin = npc->GetActorLocation();
	FNavLocation NavLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, NavLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	// FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	UE_LOG(LogTemp, Warning, TEXT("FindRandomLocation : GetRandonLocation Fail !!"));
	return EBTNodeResult::Failed;
}
