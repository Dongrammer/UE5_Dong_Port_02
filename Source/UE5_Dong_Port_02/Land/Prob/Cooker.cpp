#include "Land/Prob/Cooker.h"
#include "Character/HumanNPC.h"

ACooker::ACooker()
{
	ProbType = EProbType::E_WorkingProb;
	WorkType = EWorkType::E_Chef;
}

void ACooker::Active(ABaseHuman* human)
{
	Super::Active(human);

	// Check Distance for Select ActiveMesh
	double DistanceIn = FVector::Distance(ActiveMeshIn->GetComponentLocation(), human->GetActorLocation());
	double DistanceOut = FVector::Distance(ActiveMeshOut->GetComponentLocation(), human->GetActorLocation());

	if (DistanceIn >= DistanceOut)
	{
		human->SetActorLocation(ActiveMeshOut->GetComponentLocation() + FVector(0, 0, 100));
		human->SetActorRotation(ActiveMeshOut->GetComponentRotation() + FRotator(0, 90, 0));
	}
	else
	{
		human->SetActorLocation(ActiveMeshIn->GetComponentLocation() + FVector(0, 0, 100));
		human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));
	}

	npc = Cast<AHumanNPC>(human);

	if (npc)
		GetWorld()->GetTimerManager().SetTimer(ChangeHandle, this, &ACooker::ChangeHobby, ChangeTime, false);
}

void ACooker::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);

	if (npc)
		GetWorld()->GetTimerManager().ClearTimer(ChangeHandle);
}

void ACooker::ChangeHobby()
{
	if (npc)
	{
		npc->SetRandomHobby();
		Deactive(UsingHuman);
	}

}
