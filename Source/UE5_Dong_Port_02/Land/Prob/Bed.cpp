#include "Land/Prob/Bed.h"
#include "Character/HumanNPC.h"

ABed::ABed()
{
	ProbType = EProbType::E_RestingProb;
	RestType = ERestType::E_Sleep;

	GetUpAnim = Helper::GetAsset<UAnimMontage>(L"/Game/Animations/Life/Rest/Anim_UpToBed_MakeByDong_M");
}

void ABed::Active(ABaseHuman* human)
{
	Super::Active(human);

	double DistanceIn = FVector::Distance(ActiveMeshIn->GetComponentLocation(), human->GetActorLocation());

	human->SetActorLocation(ActiveMeshIn->GetComponentLocation() + FVector(0, 0, 100));
	human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));

	if (!TimerHandle.IsValid())
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABed::RecoveryCondition, 1.0f, true);
}

void ABed::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);

	if (GetUpAnim)
	{
		human->SetCanMove(false);
		human->PlayAnimMontage(GetUpAnim);
	}

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ABed::RecoveryCondition()
{
	if (!UsingHuman) return;

	TObjectPtr<AHumanNPC> npc = Cast<AHumanNPC>(UsingHuman);
	if (npc)
	{
		npc->RecoveryFatigue(10);
	}
}
