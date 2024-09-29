#include "Character/HumanNPC/BTTask_SetWalkSpeed.h"
#include "Character/HumanNPC/HumanNPC_AIController.h"
#include "Character/HumanNPC.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_SetWalkSpeed::UBTTask_SetWalkSpeed()
{
	NodeName = TEXT("Set Speed");
}

EBTNodeResult::Type UBTTask_SetWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get NPC
	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("BTT_InitBehavior : npc Is NULL !!"));
		return EBTNodeResult::Failed;
	}

	npc->GetCharacterMovement()->MaxWalkSpeed = Speed;
	return EBTNodeResult::Succeeded;
}
