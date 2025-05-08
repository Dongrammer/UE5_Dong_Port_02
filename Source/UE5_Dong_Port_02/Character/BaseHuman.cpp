#include "Character/BaseHuman.h"

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

	RightHandCollision = Helper::CreateActorComponent<UCapsuleComponent>(this, "RightHand Collision");
	LeftHandCollision = Helper::CreateActorComponent<UCapsuleComponent>(this, "LeftHand Collision");
	RightLegCollision = Helper::CreateActorComponent<UCapsuleComponent>(this, "RightLeg Collision");
	LeftLegCollision = Helper::CreateActorComponent<UCapsuleComponent>(this, "LeftLeg Collision");

	RightHandCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_r"));
	LeftHandCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_l"));
	RightLegCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("calf_twist_01_r"));
	LeftLegCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("calf_twist_01_l"));

	RightHandCollision->SetCollisionProfileName(TEXT("Weapon"));
	LeftHandCollision->SetCollisionProfileName(TEXT("Weapon"));
	RightLegCollision->SetCollisionProfileName(TEXT("Weapon"));
	LeftLegCollision->SetCollisionProfileName(TEXT("Weapon"));

	// Set HandCollision Transform
	{
		FRotator ro;
		FQuat rotation;
		FVector scale;
		FVector location;

		// Left Hand
		ro = FRotator(90, 0, 0);
		rotation = ro.Quaternion();
		scale = FVector(0.3, 0.3, 0.3);
		LeftHandCollision->SetRelativeRotation(rotation);
		LeftHandCollision->SetRelativeScale3D(scale);

		// Right Hand
		ro = FRotator(90, 0, 0);
		rotation = ro.Quaternion();
		scale = FVector(0.3, 0.3, 0.3);
		RightHandCollision->SetRelativeRotation(rotation);
		RightHandCollision->SetRelativeScale3D(scale);

		// Left Leg
		ro = FRotator(100, 0, 0);
		rotation = ro.Quaternion();
		scale = FVector(0.3, 0.3, 0.6);
		location = FVector(20, 0, 2);
		LeftLegCollision->SetRelativeRotation(rotation);
		LeftLegCollision->SetRelativeScale3D(scale);
		LeftLegCollision->SetRelativeLocation(location);

		// Right Leg
		ro = FRotator(100, 0, -10);
		rotation = ro.Quaternion();
		scale = FVector(0.3, 0.3, 0.6);
		location = FVector(-20, -3, -2);
		RightLegCollision->SetRelativeRotation(rotation);
		RightLegCollision->SetRelativeScale3D(scale);
		RightLegCollision->SetRelativeLocation(location);
	}

	// Hitted Point
	HighForwardPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("High Forward Point"), HittedPoints);
	HighBackPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("High Back Point"), HittedPoints);
	HighLeftPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("High Left Point"), HittedPoints);
	HighRightPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("High Right Point"), HittedPoints);
	MidForwardPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Mid Forward Point"), HittedPoints);
	MidBackPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Mid Back Point"), HittedPoints);
	MidLeftPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Mid Left Point"), HittedPoints);
	MidRightPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Mid Right Point"), HittedPoints);
	LowForwardPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Low Forward Point"), HittedPoints);
	LowBackPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Low Back Point"), HittedPoints);
	LowLeftPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Low Left Point"), HittedPoints);
	LowRightPoint = Helper::CreateSceneComponent<USceneComponent>(this, TEXT("Low Right Point"), HittedPoints);

	HighForwardPoint->SetRelativeLocation(FVector(35, 0, 75));
	HighBackPoint->SetRelativeLocation(FVector(-35, 0, 75));
	HighLeftPoint->SetRelativeLocation(FVector(0, -35, 75));
	HighRightPoint->SetRelativeLocation(FVector(0, 35, 75));
	MidForwardPoint->SetRelativeLocation(FVector(35, 0, 35));
	MidBackPoint->SetRelativeLocation(FVector(-35, 0, 35));
	MidLeftPoint->SetRelativeLocation(FVector(0, -35, 35));
	MidRightPoint->SetRelativeLocation(FVector(0, 35, 35));
	LowForwardPoint->SetRelativeLocation(FVector(35, 0, -45));
	LowBackPoint->SetRelativeLocation(FVector(-35, 0, -45));
	LowLeftPoint->SetRelativeLocation(FVector(0, -35, -45));
	LowRightPoint->SetRelativeLocation(FVector(0, 35, -45));

}

void ABaseHuman::BeginPlay()
{
	Super::BeginPlay();

	if (HighForwardPoint) HittedPointMap.Add(EHumanHittedPoint::E_HighForward, HighForwardPoint);
	if (HighBackPoint) HittedPointMap.Add(EHumanHittedPoint::E_HighBack, HighBackPoint);
	if (HighLeftPoint) HittedPointMap.Add(EHumanHittedPoint::E_HighLeft, HighLeftPoint);
	if (HighRightPoint) HittedPointMap.Add(EHumanHittedPoint::E_HighRight, HighRightPoint);
	if (MidForwardPoint) HittedPointMap.Add(EHumanHittedPoint::E_MidForward, MidForwardPoint);
	if (MidBackPoint) HittedPointMap.Add(EHumanHittedPoint::E_MidBack, MidBackPoint);
	if (MidLeftPoint) HittedPointMap.Add(EHumanHittedPoint::E_MidLeft, MidLeftPoint);
	if (MidRightPoint) HittedPointMap.Add(EHumanHittedPoint::E_MidRight, MidRightPoint);
	if (LowForwardPoint) HittedPointMap.Add(EHumanHittedPoint::E_LowForward, LowForwardPoint);
	if (LowBackPoint) HittedPointMap.Add(EHumanHittedPoint::E_LowBack, LowBackPoint);
	if (LowLeftPoint) HittedPointMap.Add(EHumanHittedPoint::E_LowLeft, LowLeftPoint);
	if (LowRightPoint) HittedPointMap.Add(EHumanHittedPoint::E_LowRight, LowRightPoint);
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

void ABaseHuman::GetGold(int val)
{
	InventoryComponent->GetGold(val);
}

void ABaseHuman::PlayPushedAnim(EPushedDirection dir, EPushType type)
{
	switch (type)
	{
	case EPushType::E_Push:
	{
		if (!PlayAnimMontage(HittedAnim->PushedAnim.FindRef(dir))) return;

		PlayAnimMontage(HittedAnim->PushedAnim.FindRef(dir));
		break;
	}
	case EPushType::E_StrongPush:
	{
		if (!PlayAnimMontage(HittedAnim->StrongPushedAnim.FindRef(dir))) return;

		PlayAnimMontage(HittedAnim->StrongPushedAnim.FindRef(dir));
		break;
	}
	}

	GetCharacterMovement()->StopActiveMovement();
	SetCanAttack(false);
	SetCanMove(false);
	SetCurrentState(EStateType::E_Hitted);
}

void ABaseHuman::PlayHittedAnim(EHumanHittedPoint dir)
{
	PlayAnimMontage(HittedAnim->HittedAnim.FindRef(dir));

	GetCharacterMovement()->StopActiveMovement();
	SetCanAttack(false);
	SetCanMove(false);
	SetCurrentState(EStateType::E_Hitted);
}

void ABaseHuman::PlayDeadAnim(EHumanHittedPoint dir)
{
	PlayAnimMontage(HittedAnim->DeadAnim.FindRef(dir));

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

void ABaseHuman::DoDashMovement()
{
}

void ABaseHuman::EndActionNotify()
{
}

void ABaseHuman::ActiveAttackCollision(EActiveCollisionType collisiontype)
{
	EActiveCollisionType type = collisiontype;

	switch (type)
	{
	case EActiveCollisionType::E_LeftPunch:
	{
		Collisions.Add(LeftHandCollision);
		break;
	}
	case EActiveCollisionType::E_RightPunch:
	{
		Collisions.Add(RightHandCollision);
		break;
	}
	case EActiveCollisionType::E_LeftKick:
	{
		Collisions.Add(LeftLegCollision);
		break;
	}
	case EActiveCollisionType::E_RightKick:
	{
		Collisions.Add(RightLegCollision);
		break;
	}
	case EActiveCollisionType::E_OneHandSword:
	{
		TObjectPtr<UCapsuleComponent> weaponCap = WeaponComponent->GetWeaponCapsule();
		Collisions.Add(weaponCap);
		break;
	}
	default:
	{
		UE_LOG(ActionCompLog, Warning, TEXT("ActiveAttackCollision : CollisionType Is NULL !!"));
		return;
	}
	}

	for (auto Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseHuman::AttackCollisionOnBeginOverlap);
	}
}

void ABaseHuman::DeactiveAttackCollision()
{
	for (auto Collision : Collisions)
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Collision->OnComponentBeginOverlap.Clear();
	}

	Collisions.Empty();
}

void ABaseHuman::AttackCollisionOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ABaseCharacter> target = Cast<ABaseCharacter>(OtherActor);

	if (!target || target == this) return;
	TArray<EStateType> ignoreState;
	ignoreState.Add(EStateType::E_Dead);
	ignoreState.Add(EStateType::E_Avoid);
	if (target->CurrentStateAre(ignoreState)) return;

	if (!HittedCharacter.Contains(target))
		HittedCharacter.AddUnique(target);

	// Calculate Damage
	int damage = CalculationDamage(StatusComponent->GetTotalStatus().ATK);

	// Calculate HitLocation
	FVector HitLocation = OverlappedComponent->GetComponentLocation();

	for (auto character : HittedCharacter)
	{
		if (!character) return;
		character->TakeDamageFuc(this, damage, HitLocation);
	}

	HittedCharacter.Empty();
}

void ABaseHuman::TakeDamageFuc(AActor* damagecauser, int damage, FVector hittedlocation)
{
	Super::TakeDamageFuc(damagecauser, damage, hittedlocation);

	// Calculate Direction
	EHumanHittedPoint HitPoint = EHumanHittedPoint::E_HighForward;
	FVector HitLocation = hittedlocation;
	float distance = FVector::Distance(HittedPointMap.FindRef(EHumanHittedPoint::E_HighForward)->GetComponentLocation(), HitLocation);
	for (int i = static_cast<uint8>(EHumanHittedPoint::E_None) + 1; i < static_cast<uint8>(EHumanHittedPoint::E_Max); i++)
	{
		EHumanHittedPoint point = static_cast<EHumanHittedPoint>(i);
		float dist = FVector::Distance(HittedPointMap.FindRef(point)->GetComponentLocation(), HitLocation);

		if (dist < distance)
		{
			HitPoint = point;
			distance = dist;
		}
	}

	StatusComponent->UpdateHP(damage);

	if (StatusComponent->CheckDead())
	{
		PlayDeadAnim(HitPoint);
	}
	else
	{
		PlayHittedAnim(HitPoint);
	}

}

int ABaseHuman::CalculationDamage(int characterATK)
{
	return characterATK;
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

void ABaseHuman::SetCurrentWeapon(TObjectPtr<ABaseWeapon> weapon)
{
	WeaponComponent->SetCurrentWeapon(weapon);
}
