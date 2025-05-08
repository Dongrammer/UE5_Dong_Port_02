#include "Notify/EquipWeapon.h"

#include "Character/BaseHuman.h"
#include "Component/WeaponComponent.h"

void UEquipWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(MeshComp->GetOwner());

	if (!human) return;

	human->GetWeaponComponent()->WeaponHolding();
}
