#include "Notify/DoActionMovement.h"

#include "Character/Hero.h"
#include "Component/ActionComponent.h"
#include "Action/BaseAction.h"

/*
	�׼��� ���� ���� �̵��Ÿ��� �ٸ� ��, �������Ʈ���� ������ Ÿ�Ӷ����� �߰��ؼ� Switch�� �����ؾ���.
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
