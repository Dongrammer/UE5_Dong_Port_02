#include "Action/BaseDash.h"

#include "Character/Hero.h"
#include "Component/ActionComponent.h"

DEFINE_LOG_CATEGORY(DashActionLog);

/*
	Start, End Location이 필요할 때는 블루프린트에서 SetLocation 호출
*/

ABaseDash::ABaseDash()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseDash::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseDash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseDash::SettingOwner(TObjectPtr<AHero> InOwner)
{
	ActionOwner = InOwner;
}

void ABaseDash::PressedDash()
{
	if (!bCanMove)
	{
		ActionOwner->SetCanMove(false);
	}

	bHolding = true;
	direction = ActionOwner->GetInputDirection();

	if (!AnimAsset.FindRef(direction))
	{
		UE_LOG(DashActionLog, Warning, TEXT("DashAction [%s] : AnimAsset Is NULL !!"), GetFName());
		return;
	}

	ActionOwner->PlayAnimMontage(AnimAsset.FindRef(direction));
}

void ABaseDash::ReleasedDash()
{
	bHolding = false;
}

void ABaseDash::SetLocation()
{
	FVector Start = ActionOwner->GetActorLocation();
	FVector End = Start;

	switch (direction)
	{
	case EInputDirection::E_Forward:
	{
		End += DashDistance * ActionOwner->GetActorForwardVector().GetSafeNormal();
		break;
	}
	case EInputDirection::E_Back:
	{
		End += DashDistance * ActionOwner->GetActorForwardVector().GetSafeNormal() * -1;
		break;
	}
	case EInputDirection::E_Right:
	{
		End += DashDistance * ActionOwner->GetActorRightVector().GetSafeNormal();
		break;
	}
	case EInputDirection::E_Left:
	{
		End += DashDistance * ActionOwner->GetActorRightVector().GetSafeNormal() * -1;
		break;
	}
	}

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(ActionOwner);

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1, 0, 1);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectParams, Params);

	if (HitResult.bBlockingHit && IsValid(HitResult.GetActor()))
	{
		float distance = 0;
		if (HitResult.Distance >= ActionOwner->GetCapsuleRadius())
			distance = HitResult.Distance - ActionOwner->GetCapsuleRadius();
		else
			distance = 0;

		switch (direction)
		{
		case EInputDirection::E_Forward:
		{
			End = Start + (distance * ActionOwner->GetActorForwardVector().GetSafeNormal());
			break;
		}
		case EInputDirection::E_Back:
		{
			End = Start - (distance * ActionOwner->GetActorForwardVector().GetSafeNormal());
			break;
		}
		case EInputDirection::E_Right:
		{
			End = Start + (distance * ActionOwner->GetActorRightVector().GetSafeNormal());
			break;
		}
		case EInputDirection::E_Left:
		{
			End = Start - (distance * ActionOwner->GetActorRightVector().GetSafeNormal());
			break;
		}
		}

	}

	StartLocation = Start;
	EndLocation = End;
}

