#include "Notify/EndAction.h"

#include "Character/BaseHuman.h"

void UEndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(MeshComp->GetOwner());
	
	if (!human) return;
	human->EndActionNotify();
}
