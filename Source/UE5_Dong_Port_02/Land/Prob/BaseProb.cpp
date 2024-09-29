#include "Land/Prob/BaseProb.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY(ProbLog);

ABaseProb::ABaseProb()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	Body = Helper::CreateSceneComponent<USceneComponent>(this, "Architecture", Scene);
	ActiveMeshIn = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Active Mesh In", Scene);
	ActiveMeshOut = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Active Mesh Out", Scene);

	StimulusSource = Helper::CreateActorComponent<UAIPerceptionStimuliSourceComponent>(this, "Stimulus");

}

void ABaseProb::BeginPlay()
{
	Super::BeginPlay();

	// Check Safe
	switch (ProbType)
	{
	case EProbType::E_None:
	{
		UE_LOG(ProbLog, Warning, TEXT("ProbType Error !!"));
		return;
	}
	case EProbType::E_WorkingProb:
	{
		if (WorkType == EWorkType::E_None)
		{
			UE_LOG(ProbLog, Warning, TEXT("%s : WorkType Error !!"), *this->GetFName().ToString());
			return;
		}
		break;
	}
	case EProbType::E_RestingProb:
	{
		if (RestType == ERestType::E_None)
		{
			UE_LOG(ProbLog, Warning, TEXT("%s : RestType Error !!"), *this->GetFName().ToString());
			return;
		}
		break;
	}
	case EProbType::E_OneTimeProb:
	{
		if (InteractionType == EInteractionType::E_None)
		{
			UE_LOG(ProbLog, Warning, TEXT("%s : InteractionType Error !!"), *this->GetFName().ToString());
			return;
		}
		break;
	}
	}

	// Perception
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(UAISense_Sight::StaticClass());
		StimulusSource->RegisterWithPerceptionSystem();

	}
}

void ABaseProb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProb::Active(ABaseHuman* human)
{
	if (human->GetUsingProb()) return;

	switch (ProbType)
	{
	case EProbType::E_WorkingProb:
	{
		Used = true;
		UsingHuman = human;

		human->SetBehavior(EBehaviorType::E_Working);
		human->SetUsingProb(this);
		human->PlayWorkAnim(WorkType);
		break;
	}
	case EProbType::E_RestingProb:
	{
		Used = true;
		UsingHuman = human;

		human->SetBehavior(EBehaviorType::E_Resting);
		human->SetUsingProb(this);
		human->PlayRestingAnim(RestType);
		break;
	}
	case EProbType::E_OneTimeProb:
	{
		human->PlayInteractionAnim(InteractionType);
		break;
	}
	}
}

void ABaseProb::Deactive(ABaseHuman* human)
{

	switch (ProbType)
	{
	case EProbType::E_WorkingProb:
	{
		Used = false;
		UsingHuman = nullptr;

		if (human->CheckBehavior(EBehaviorType::E_Working))
			human->SetBehavior(EBehaviorType::E_None);
		human->SetUsingProb(nullptr);
		human->StopWorkAnim(WorkType);
		break;
	}
	case EProbType::E_RestingProb:
	{
		Used = false;
		UsingHuman = nullptr;

		human->SetBehavior(EBehaviorType::E_None);
		human->SetUsingProb(nullptr);
		human->StopWorkAnim(WorkType);
		break;
	}
	case EProbType::E_OneTimeProb:
	{
		break;
	}
	}
}

void ABaseProb::PreActive(ABaseHuman* human)
{
}