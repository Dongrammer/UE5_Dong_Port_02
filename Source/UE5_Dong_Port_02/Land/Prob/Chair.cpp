#include "Land/Prob/Chair.h"
#include "Character/HumanNPC.h"

AChair::AChair()
{
	ProbType = EProbType::E_RestingProb;
	RestType = ERestType::E_Seet;
}

void AChair::Active(ABaseHuman* human)
{
	Super::Active(human);

	human->SetActorLocation(ActiveMeshIn->GetComponentLocation());
	human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90 + 180, 0));

	if (!TimerHandle.IsValid())
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AChair::RecoveryCondition, 1.0f, true);
}

void AChair::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AChair::RecoveryCondition()
{
	if (!UsingHuman) return;

	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(UsingHuman);
	if (npc)
	{
		npc->RecoveryFatigue(10);
	}
}
