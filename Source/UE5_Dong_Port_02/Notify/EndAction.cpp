#include "Notify/EndAction.h"

#include "Character/Hero.h"
#include "Component/ActionComponent.h"

void UEndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<AHero> hero = Cast<AHero>(MeshComp->GetOwner());
	
	if (!hero) return;
	hero->GetActionComponent()->OnEndActionNotify();
}
