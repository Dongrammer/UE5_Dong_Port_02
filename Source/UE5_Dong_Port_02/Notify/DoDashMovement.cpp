#include "Notify/DoDashMovement.h"

#include "Character/Hero.h"

void UDoDashMovement::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<AHero> hero = Cast<AHero>(MeshComp->GetOwner());

	if (!hero)
	{
		UE_LOG(LogTemp, Warning, TEXT("DoDashMovement : Hero Is NULL !!"));
		return;
	}

	hero->DoDashMovement();
}
