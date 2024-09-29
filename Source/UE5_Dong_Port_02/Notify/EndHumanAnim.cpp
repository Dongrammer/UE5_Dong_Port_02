#include "Notify/EndHumanAnim.h"
#include "Character/BaseHuman.h"

void UEndHumanAnim::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(MeshComp->GetOwner());

	if (!human)
	{
		UE_LOG(LogTemp, Warning, TEXT("AN_EndHumanAnim : human Is NULL !!"));
		return;
	}

	human->SetCanMove(true);
	human->SetCanAttack(true);
}
