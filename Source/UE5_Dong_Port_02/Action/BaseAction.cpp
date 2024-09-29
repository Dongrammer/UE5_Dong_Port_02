#include "Action/BaseAction.h"
#include "Character/Hero.h"

#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY(ActionLog);

/*
	Start, End Location이 필요할 때는 블루프린트에서 SetLocation 호출
*/

ABaseAction::ABaseAction()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseAction::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseAction::SettingOwner(TObjectPtr<AHero> InOwner)
{
	ActionOwner = InOwner;
}

void ABaseAction::DoAction()
{
	if (!AnimAsset)
	{
		UE_LOG(ActionLog, Warning, TEXT("Action [%s] : AnimAsset Is NULL !!"), GetFName());
		return;
	}

	float AnimSpeed = PlayRate + ActionOwner->GetPlayRate() - 1.0f;
	ActionOwner->PlayAnimMontage(AnimAsset, AnimSpeed);
}

void ABaseAction::SetLocation()
{
	FVector Start = ActionOwner->GetActorLocation();
	FVector End = Start + MoveDistance * ActionOwner->GetActorForwardVector().GetSafeNormal();


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

		End = Start + (distance * ActionOwner->GetActorForwardVector().GetSafeNormal());
	}

	StartLocation = Start;
	EndLocation = End;
}

void ABaseAction::PassiveSpeedUp()
{
	if (!AnimAsset)
	{
		UE_LOG(ActionLog, Warning, TEXT("PassiveSpeedUp : AnimAsset Is NULL !!"));
		return;
	}

	SpeedLevel++;
	PlayRate = SpeedLevelData.FindRef(SpeedLevel);

}
