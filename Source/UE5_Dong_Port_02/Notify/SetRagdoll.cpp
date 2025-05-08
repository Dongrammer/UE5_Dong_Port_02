#include "Notify/SetRagdoll.h"
#include "Character/BaseCharacter.h"

void USetRagdoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	TObjectPtr<ABaseCharacter> character = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (!character)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetRagdoll : character is NULL !!"));
		return;
	}

	character->SetRagdoll();
}
