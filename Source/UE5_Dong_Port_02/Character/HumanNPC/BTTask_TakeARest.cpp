#include "Character/HumanNPC/BTTask_TakeARest.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "Land/Prob/Chair.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_TakeARest::UBTTask_TakeARest()
{
	NodeName = TEXT("Take A Rest");
}

EBTNodeResult::Type UBTTask_TakeARest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Controller
	TObjectPtr<AHumanNPC_AIController> cont = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());
	if (!cont)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_TakeARset : cont Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	// Get NPC
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_TakeARset : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}




	// Get Sphere Trace HitResult
	TArray<TObjectPtr<ABaseProb>> probs = npc->SphereTraceForBaseProbs(1000.0f);
	TObjectPtr<AChair> SelectedChair;
	float distance = 0;
	for (TObjectPtr<ABaseProb> prob : probs)
	{
		TObjectPtr<AChair> chair = Cast<AChair>(prob);

		if (chair)
		{
			if (distance == 0)
			{
				SelectedChair = chair;
				distance = npc->GetDistanceTo(chair);
			}
			else if (distance > npc->GetDistanceTo(chair))
			{
				SelectedChair = chair;
				distance = npc->GetDistanceTo(chair);
			}
		}
	}

	if (SelectedChair)
	{
		FVector loc = SelectedChair->GetActiveMeshInLocation();
		EPathFollowingRequestResult::Type t = cont->MoveToLocation(loc, 5.0f, false);

		if (t == EPathFollowingRequestResult::RequestSuccessful)
		{
			return EBTNodeResult::Succeeded;
		}
		else if (t == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			UE_LOG(LogTemp, Log, TEXT("TakeARest : AlreadyAtGoal"));
			SelectedChair->Active(npc);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else if (RestAnims.Num() > 0)
	{
		uint8 rand = FMath::RandRange(0, RestAnims.Num() - 1);
		UE_LOG(LogTemp, Log, TEXT("Take A Rest : PlayAnim [%d]"), rand);
		npc->PlayAnimMontage(RestAnims[rand]);
		npc->SetCanAttack(false);
		npc->SetCanMove(false);
		npc->RecoveryFatigue(100);
	}


	return EBTNodeResult::Failed;
}
