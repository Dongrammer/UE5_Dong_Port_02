#include "Notify/EndDash.h"

#include "Character/Hero.h"
#include "Component/ActionComponent.h"

void UEndDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<AHero> hero = Cast<AHero>(MeshComp->GetOwner());

	if (!hero) return;
	hero->GetActionComponent()->OnEndDashNotify();
}
