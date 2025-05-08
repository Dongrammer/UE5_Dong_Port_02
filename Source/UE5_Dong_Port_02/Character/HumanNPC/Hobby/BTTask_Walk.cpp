#include "Character/HumanNPC/Hobby/BTTask_Walk.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "Land/BaseVillage.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Walk::UBTTask_Walk()
{
	NodeName = TEXT("Walking");
}

EBTNodeResult::Type UBTTask_Walk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//FTaskWalkNodeMemory* memory = (FTaskWalkNodeMemory*)NodeMemory;
	/*TObjectPtr<AHumanNPC> npc = memory->npc;
	TObjectPtr<ABaseVillage> village = memory->village;*/
	// Get Player
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

	if (!npc->GetCanMove())
		return EBTNodeResult::Failed;

	TObjectPtr<ABaseVillage> vil = npc->GetVillage();
		if (!vil)
		{
			UE_LOG(LogTemp, Warning, TEXT("Task_Walk : Village Is NULL !!"));
			return EBTNodeResult::Failed;
		}

	FVector location = OwnerComp.GetBlackboardComponent()->GetValueAsVector("TargetLocation");

	EPathFollowingRequestResult::Type t = OwnerComp.GetAIOwner()->MoveToLocation(location, 100.0f, false);

	if (t == EPathFollowingRequestResult::RequestSuccessful)
	{
		return EBTNodeResult::Succeeded;
	}
	else if (t == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), vil->GetRandomLocation());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Type();
}
//
//void UBTTask_Walk::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
//{
//	if (Result.Code == EPathFollowingResult::Blocked || Result.Code == EPathFollowingResult::OffPath)
//	{
//		
//	}
//}
//
//void UBTTask_Walk::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
//
//	FTaskWalkNodeMemory* memory = (FTaskWalkNodeMemory*)NodeMemory;
//
//	// Get Player
//	TObjectPtr<AHumanNPC_AIController> cont = Cast<AHumanNPC_AIController>(OwnerComp.GetAIOwner());
//	if (!cont)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Task_Walk : NPC Controller Is NULL !!"));
//		return;
//	}
//	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(cont->GetPawn());
//	if (!npc)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Task_Walk : NPC Is NULL !!"));
//		return;
//	}
//
//	memory->cont = cont;
//	memory->npc = npc;
//
//	// Get GameInstance
//	TObjectPtr<ABaseVillage> vil = npc->GetVillage();
//	if (!vil)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Task_Walk : Village Is NULL !!"));
//		return;
//	}
//
//	memory->village = vil;
//}
//
//uint16 UBTTask_Walk::GetInstanceMemorySize() const
//{
//	return sizeof(FTaskWalkNodeMemory);
//}
