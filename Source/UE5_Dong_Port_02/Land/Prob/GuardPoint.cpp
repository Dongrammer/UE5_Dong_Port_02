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
	if (UsingHuman)
	{
		Deactive(UsingHuman);
	}

	Super::PreActive(human);

	Used = true;
	UsingHuman = human;
}

void AGuardPoint::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);
	UE_LOG(LogTemp, Log, TEXT("GuardPoint : Deactive Call !!"));

	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(human);
	if (!npc)
	{
		UE_LOG(LogTemp, Warning, TEXT("GuardPoint : npc Castint Fail !!"));
		return;
	}

	if (!(npc->GetCurrentRoutine() == ERoutineType::E_GoWork))
	{
		UE_LOG(LogTemp, Log, TEXT("GuardPoint : CurrentRoutine Not GoWork !!"));
		PrevHuman = human;
		PrevHuman->SetCanMove(false);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AGuardPoint::CheckHumanNearby, 1.0f, true);
	}
}

void AGuardPoint::CheckHumanNearby()
{
	if (!UsingHuman) return;

	TArray<TEnumAsByte<EObjectTypeQuery>> objType;
	TEnumAsByte<EObjectTypeQuery> TraceObjectType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	objType.Add(TraceObjectType);

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
			return;
		}
	}
}
