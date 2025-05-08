#include "Character/HumanNPC/Hobby/BTTask_Cooking.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "Land/Building/Building.h"
#include "Land/Prob/Cooker.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_Cooking::UBTTask_Cooking()
{
	NodeName = TEXT("Cooking");
}

EBTNodeResult::Type UBTTask_Cooking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Cooking : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	if (!npc->GetCanMove())
		return EBTNodeResult::Failed;

	TObjectPtr<ABuilding> home = npc->GetHome();

	if (!home)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Cooking : home Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	TArray<TObjectPtr<ACooker>> cookers = home->GetInsideProbs<ACooker>();

	if (cookers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_Cooking : Cookers Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	TObjectPtr<ACooker> cooker;
	
	for (int i = 0; i < cookers.Num(); i++)
	{
		if (!cookers[i]->GetUsed())
		{
			cooker = cookers[i];
			break;
		}
	}

	if (!cooker)
	{
		return EBTNodeResult::Failed;
	}

	FVector loc = cooker->GetActiveMeshInLocation();
	EPathFollowingRequestResult::Type t = OwnerComp.GetAIOwner()->MoveToLocation(loc, 20.0f, false);

	if (t == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::Succeeded;
	}
	else if (t == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		cooker->Active(npc);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Type();
}

void UBTTask_Cooking::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
