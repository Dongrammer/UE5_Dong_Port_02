#include "Notify/SetNextAction.h"

#include "Character/Hero.h"
#include "Component/ActionComponent.h"

void USetNextAction::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void USetNextAction::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	TObjectPtr<AHero> hero = Cast<AHero>(MeshComp->GetOwner());
	// Check bSafe
	if (!hero)
	{
		return;
	}
	TObjectPtr<UActionComponent> actionComp = hero->GetActionComponent();
	if (!actionComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetNextAction : ActionComp Is NULL !!"));
		return;
	}

	// 
	if (hero->bLeftClicked)
	{
		actionComp->bNextAction = true;
	}
}

void USetNextAction::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
