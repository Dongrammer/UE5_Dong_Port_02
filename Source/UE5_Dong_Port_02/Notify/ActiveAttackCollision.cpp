#include "Notify/ActiveAttackCollision.h"
#include "../Character/BaseHuman.h"

void UActiveAttackCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(MeshComp->GetOwner());

	if (!human)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANS_ActiveAttackCollision : human Is NULL !!"));
		return;
	}

	human->ActiveAttackCollision(ActiveCollisionType);
}

void UActiveAttackCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(MeshComp->GetOwner());

	if (!human)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANS_ActiveAttackCollision : human Is NULL !!"));
		return;
	}

	human->DeactiveAttackCollision();
}
