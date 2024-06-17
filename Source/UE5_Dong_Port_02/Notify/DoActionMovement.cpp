#include "Notify/DoActionMovement.h"

#include "Character/Hero.h"
#include "Component/ActionComponent.h"
#include "Action/BaseAction.h"

/*
	액션의 레벨 별로 이동거리가 다를 시, 블루프린트에서 레벨별 타임라인을 추가해서 Switch로 연결해야함.
*/

void UDoActionMovement::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<AHero> hero = Cast<AHero>(MeshComp->GetOwner());
	
	if (!hero)
	{
		UE_LOG(LogTemp, Warning, TEXT("DoActionMovement : Hero Is NULL !!"));
		return;
	}

	hero->GetActionComponent()->GetNowAction()->DoActionMovement();
}
