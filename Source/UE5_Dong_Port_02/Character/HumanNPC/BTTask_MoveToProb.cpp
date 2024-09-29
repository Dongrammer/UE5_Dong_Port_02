#include "Character/HumanNPC/BTTask_MoveToProb.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Land/Prob/BaseProb.h"
#include "Navigation/PathFollowingComponent.h"
#include "Land/Building/Building.h"
#include "Land/Prob/Bed.h"

UBTTask_MoveToProb::UBTTask_MoveToProb()
{
	NodeName = TEXT("Move To Prob");
}

EBTNodeResult::Type UBTTask_MoveToProb::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get NPC
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveToProb : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	if (!npc->GetCanMove())
		return EBTNodeResult::Failed;

	// Get & Set Prob
	ERoutineType routine = npc->GetCurrentRoutine();
	TObjectPtr<ABaseProb> prob;
	switch (routine)
	{
	case ERoutineType::E_GoWork:
	{
		prob = Cast<ABaseProb>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("WorkProb"));

		if (!prob)
		{
			TArray<TObjectPtr<ABaseProb>> probs = npc->GetWorkProbs();

			if (probs.Num() == 0)
				return EBTNodeResult::Failed;

			int32 RandNum = FMath::RandRange(0, probs.Num() - 1);
			prob = probs[RandNum];
			if (!prob->GetUsed())
			{
				prob->PreActive(npc);
				OwnerComp.GetBlackboardComponent()->SetValueAsObject("WorkProb", prob);
			}
			else
			{
				for (auto& p : probs)
				{
					if (!p->GetUsed())
					{
						prob = p;
						prob->PreActive(npc);
						OwnerComp.GetBlackboardComponent()->SetValueAsObject("WorkProb", prob);
						break;
					}
				}
			}
		}
		break;
	}
	case ERoutineType::E_GoHome:
		break;
	case ERoutineType::E_Sleep:
	{
		TArray<TObjectPtr<ABed>> probs = npc->GetHome()->GetInsideProbs<ABed>();

		if (probs.Num() == 0)
			return EBTNodeResult::Failed;

		for (TObjectPtr<ABed> p : probs)
		{
			if (!p->GetUsed())
			{
				prob = p;
				break;
			}
		}
		break;
	}
	}

	


	// Move To Prob And Active
	FVector loc = prob->GetActiveMeshInLocation();
	EPathFollowingRequestResult::Type t = OwnerComp.GetAIOwner()->MoveToLocation(loc, 20.0f, false);

	if (t == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::Succeeded;
	}
	else if (t == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		prob->Active(npc);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Type();
}

void UBTTask_MoveToProb::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	TObjectPtr<AAIController> cont = OwnerComp.GetAIOwner();
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_MoveToProb : npc Is NULL !!"));
		return;
	}

	if (!npc->GetCanMove())
	{
		cont->StopMovement();
	}

	return;
}
