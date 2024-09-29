#include "Land/Prob/Anvil.h"

AAnvil::AAnvil()
{
	ProbType = EProbType::E_WorkingProb;
	WorkType = EWorkType::E_UseAnvil;
}

void AAnvil::Active(ABaseHuman* human)
{
	Super::Active(human);

	// Check Distance for Select ActiveMesh
	double DistanceIn = FVector::Distance(ActiveMeshIn->GetComponentLocation(), human->GetActorLocation());
	double DistanceOut = FVector::Distance(ActiveMeshOut->GetComponentLocation(), human->GetActorLocation());

	if (DistanceIn >= DistanceOut)
	{
		human->SetActorLocation(ActiveMeshOut->GetComponentLocation());
		human->SetActorRotation(ActiveMeshOut->GetComponentRotation() + FRotator(0, 90, 0));
	}
	else
	{
		human->SetActorLocation(ActiveMeshIn->GetComponentLocation());
		human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));
	}
}