#include "Character/BaseHuman.h"

#include "Component/InventoryComponent.h"
#include "Component/EquipComponent.h"
#include "Hero.h"
#include "Helper.h"
#include "Land/Prob/BaseProb.h"
#include "Kismet/KismetSystemLibrary.h"

ABaseHuman::ABaseHuman()
{
	BodyCollision->InitCapsuleSize(35.0f, 96.0f);

	InventoryComponent = Helper::CreateActorComponent<UInventoryComponent>(this, "Inventory Component");
	WeaponComponent = Helper::CreateActorComponent<UWeaponComponent>(this, "Weapon Component");
	EquipComponent = Helper::CreateActorComponent<UEquipComponent>(this, "Equip Component");

	EquipComponent->GetWeaponComponent(WeaponComponent);

	LifeAnims = Helper::GetAsset<ULifeAnimDataAsset>(L"/Game/Characters/DA_LifeAnims");
	HittedAnim = Helper::GetAsset<UHittedAnimAsset>(L"/Game/Characters/DA_HittedAnims");
}

void ABaseHuman::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseHuman::CreateCharacter()
{
	Super::CreateCharacter();
	// Mesh Setting
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>(L"/Game/Characters/Base/Mannequins/Meshes/SKM_Manny"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ABaseHuman::SetCharacterMovement()
{
	Super::SetCharacterMovement();
}

void ABaseHuman::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABaseHuman::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseHuman::Pushed(FVector direction, float force)
{
}

void ABaseHuman::PlayHittedAnim(EHittedDirection dir, EHittedType type)
{
	switch (type)
	{
	case EHittedType::E_Push:
	{
		if (!PlayAnimMontage(HittedAnim->PushedAnim.FindRef(dir))) return;

		PlayAnimMontage(HittedAnim->PushedAnim.FindRef(dir));
		break;
	}
	case EHittedType::E_StrongPush:
	{
		if (!PlayAnimMontage(HittedAnim->StrongPushedAnim.FindRef(dir))) return;

		PlayAnimMontage(HittedAnim->StrongPushedAnim.FindRef(dir));
		break;
	}
	}

	GetCharacterMovement()->StopActiveMovement();
	SetCanAttack(false);
	SetCanMove(false);
}

void ABaseHuman::SetPlayRate(float playrate)
{
	PlayRate = playrate;
	SetWalkSpeed(GetStandardWalkSpeed() * playrate);
}

void ABaseHuman::PlayInteractionAnim(EInteractionType type)
{
	if (LifeAnims->InteractionAnim.FindRef(type))
	{
		GetCharacterMovement()->StopActiveMovement();
		SetCanAttack(false);
		SetCanMove(false);
		PlayAnimMontage(LifeAnims->InteractionAnim.FindRef(type), PlayRate);
	}
}

void ABaseHuman::PlayWorkAnim(EWorkType type)
{
	StartWork(type);
	if (LifeAnims->WorkAnim.FindRef(type))
	{
		GetCharacterMovement()->StopActiveMovement();
		SetCanAttack(false);
		SetCanMove(false);
		PlayAnimMontage(LifeAnims->WorkAnim.FindRef(type));
	}
}

void ABaseHuman::PlayRestingAnim(ERestType type)
{
	if (LifeAnims->RestAnim.FindRef(type))
	{
		GetCharacterMovement()->StopActiveMovement();
		SetCanAttack(false);
		SetCanMove(false);
		PlayAnimMontage(LifeAnims->RestAnim.FindRef(type));
	}
}

void ABaseHuman::StopWorkAnim(EWorkType type)
{
	StopWork();
	SetCanAttack(true);
	SetCanMove(true);
	StopAnimMontage(LifeAnims->WorkAnim.FindRef(type));
}

void ABaseHuman::StartWork(EWorkType type)
{
}

void ABaseHuman::StopWork()
{
}

EWorkType ABaseHuman::GetCurrentWorkingType()
{
	return UsingProb->GetWorkType();
}

TArray<TObjectPtr<ABaseProb>> ABaseHuman::SphereTraceForBaseProbs(float radius)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> objType;
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	objType.Add(WorldDynamic);

	TArray<TObjectPtr<AActor>> actor;
	TArray<FHitResult> hitResult;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		this, 
		GetActorLocation(), 
		GetActorLocation(), 
		radius, 
		objType, 
		false, 
		actor, 
		EDrawDebugTrace::ForDuration, 
		hitResult,
		true);

	// Check BaseProb
	TArray<TObjectPtr<ABaseProb>> result;
	for (FHitResult re : hitResult)
	{
		TObjectPtr<ABaseProb> prob = Cast<ABaseProb>(re.GetActor());
		if (prob)
			result.Add(prob);
	}

	return result;
}

void ABaseHuman::GetItems(FItemData item, int count)
{
	InventoryComponent->GetItems(item, count);
}

bool ABaseHuman::CheckItemWeight(float itemweight)
{
	if (InventoryComponent->CheckWeight(itemweight))
		return true;
	else
	{
		return false;
	}
}

bool ABaseHuman::GetWeaponHolding()
{
	return WeaponComponent->GetWeaponHolding();
}

void ABaseHuman::SetCurrentWeaponType(EWeaponType type)
{
	WeaponComponent->SetCurrentWeaponType(type);
}
