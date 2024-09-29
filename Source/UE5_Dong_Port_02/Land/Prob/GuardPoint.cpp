#include "Land/Prob/GuardPoint.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/HumanNPC.h"

AGuardPoint::AGuardPoint()
{
	ProbType = EProbType::E_WorkingProb;
	WorkType = EWorkType::E_Guard;
	bCanPlayerUse = false;
}

void AGuardPoint::Active(ABaseHuman* human)
{
	Super::Active(human);
	
	if (FVector::Distance(this->GetActiveMeshInLocation(), human->GetActorLocation()) > 100.0f)
		human->SetActorLocation(ActiveMeshIn->GetComponentLocation());
	
	FRotator TargetRotator = ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0);
	FRotator HumanRotator = human->GetActorRotation();
	if (!TargetRotator.Equals(HumanRotator, 10.0f))
		human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));
}

void AGuardPoint::PreActive(ABaseHuman* human)
{
	Super::PreActive(human);

	Used = true;
	UsingHuman = human;
}

void AGuardPoint::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);

	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(human);
	if (!npc) return;
	if (!(npc->GetCurrentRoutine() == ERoutineType::E_GoWork))
	{
		PrevHuman = human;
		PrevHuman->SetCanMove(false);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGuardPoint::CheckHumanNearby, 1.0f, true);
	}
}

void AGuardPoint::CheckHumanNearby()
{
	if (!UsingHuman) return;

	TArray<TEnumAsByte<EObjectTypeQuery>> objType;
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	objType.Add(WorldDynamic);

	TArray<TObjectPtr<AActor>> Ignoreactors;
	Ignoreactors.Add(PrevHuman);
	TArray<FHitResult> hitResult;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		GetActorLocation(),
		GetActorLocation(),
		500.0f,
		objType,
		false,
		Ignoreactors,
		EDrawDebugTrace::ForDuration,
		hitResult,
		true
	);

	if (hitResult.Num() == 0) return;

	for (FHitResult re : hitResult)
	{
		TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(re.GetActor());
		if (npc == UsingHuman)
		{
			PrevHuman->SetCanMove(true);
			PrevHuman = nullptr;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
}
