#include "Character/HumanNPC/Hobby/BTT_RestAtHome.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "Land/Building/Building.h"
#include "Land/Prob/Chair.h"
#include "Land/Prob/Bed.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_RestAtHome::UBTT_RestAtHome()
{
	NodeName = TEXT("RestAtHome");
}

EBTNodeResult::Type UBTT_RestAtHome::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Set Random
	TaskMemoryRestAtHome* memory = (TaskMemoryRestAtHome*)(NodeMemory);
	bool bRandomSet = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("bRandomSet"));

	if (bRandomSet == false)
	{
		// Get NPC
		TObjectPtr<AHumanNPC_AIController> cont = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());
		if (!cont)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Walk : NPC Controller Is NULL !!"));
			return EBTNodeResult::Failed;
		}
		TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
		if (!npc)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Walk : NPC Is NULL !!"));
			return EBTNodeResult::Failed;
		}
		if (npc->GetUsingProb()) npc->GetUsingProb()->Deactive(npc);
		// Get Home
		TObjectPtr<ABuilding> home = npc->GetHome();
		if (!home)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Walk : Village Is NULL !!"));
			return EBTNodeResult::Failed;
		}
		memory->cont = cont;
		memory->npc = npc;
		memory->home = home;

		memory->RandomInt = FMath::RandRange(0, 9);

		// Set Location
		FVector location;
		TObjectPtr<ABaseProb> prob;

		int rand = memory->RandomInt;
		float changeSec = 0;
		if (rand < 6) // FindRandomLocation In Home
		{
			location = home->GetRandomLocation();
			changeSec = 10.0f;
		}
		else if (rand < 8) // Rest at Chair
		{
			TArray<TObjectPtr<AChair>> chairs = home->GetInsideProbs<AChair>();

			if (chairs.Num() != 0)
			{
				int r = FMath::RandRange(0, chairs.Num() - 1);
				prob = chairs[r];
				location = prob->GetActiveMeshInLocation();
				changeSec = 30.0f;
			}
		}
		else // Rest at bed
		{
			TArray<TObjectPtr<ABed>> beds = home->GetInsideProbs<ABed>();

			if (beds.Num() != 0)
			{
				int r = FMath::RandRange(0, beds.Num() - 1);
				prob = beds[r];
				location = prob->GetActiveMeshInLocation();
				changeSec = 60.0f;
			}
		}

		memory->TargetLocation = location;
		memory->prob = prob;

		// Bind
		GetWorld()->GetTimerManager().ClearTimer(memory->timerhandle);

		FTimerDelegate timerdel;
		timerdel.BindUObject(this, &UBTT_RestAtHome::ChangeAction, OwnerComp.GetBlackboardComponent());
		GetWorld()->GetTimerManager().SetTimer(memory->timerhandle, timerdel, changeSec, false);

		//UE_LOG(LogTemp, Log, TEXT("RandomSet Call : %d"), memory->RandomInt);

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bRandomSet"), true);
	}

	if (!memory->npc)
	{
		UE_LOG(LogTemp, Log, TEXT("memory npc is null !!"));
		return EBTNodeResult::Failed;
	}
	if (!memory->npc->GetCanMove())
		return EBTNodeResult::Failed;

	//// Get RestProb
	//FVector location;
	//TObjectPtr<ABaseProb> prob;

	//if (!memory->bInAction)
	//{
	//	int rand = memory->RandomInt;
	//	float changeSec = 0;
	//	if (rand < 6) // FindRandomLocation In Home
	//	{
	//		location = home->GetRandomLocation();
	//		changeSec = 20.0f;
	//	}
	//	else if (rand < 8) // Rest at Chair
	//	{
	//		TArray<TObjectPtr<AChair>> chairs = home->GetInsideProbs<AChair>();

	//		if (chairs.Num() != 0)
	//		{
	//			int r = FMath::RandRange(0, chairs.Num() - 1);
	//			prob = chairs[r];
	//			location = prob->GetActiveMeshInLocation();
	//		}
	//	}
	//	else // Rest at bed
	//	{
	//		TArray<TObjectPtr<ABed>> beds = home->GetInsideProbs<ABed>();

	//		if (beds.Num() != 0)
	//		{
	//			int r = FMath::RandRange(0, beds.Num() - 1);
	//			prob = beds[r];
	//			location = prob->GetActiveMeshInLocation();
	//		}
	//	}

	//	memory->bInAction = true;
	//}

	EPathFollowingRequestResult::Type t = OwnerComp.GetAIOwner()->MoveToLocation(memory->TargetLocation, 20.0f, false);
	//DrawDebugLine(GetWorld(), memory->TargetLocation, memory->TargetLocation + FVector(0, 0, 200), FColor::Black, true, 10.0f, 0, 5.0f);
	if (t == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::Succeeded;
	}
	else if (t == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		if (memory->prob)
		{
			memory->prob->Active(memory->npc);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Type();
}

uint16 UBTT_RestAtHome::GetInstanceMemorySize() const
{
	return sizeof(TaskMemoryRestAtHome);
}

void UBTT_RestAtHome::ChangeAction(UBlackboardComponent* blackboard)
{
	//UE_LOG(LogTemp, Log, TEXT("ChangeAction Call"));
	blackboard->SetValueAsBool(TEXT("bRandomSet"), false);
}
