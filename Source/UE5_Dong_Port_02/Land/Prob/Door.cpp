#include "Land/Prob/Door.h"

#include "Components/SceneComponent.h"
#include "Navigation/NavLinkProxy.h"
#include "NavLinkCustomComponent.h"

ADoor::ADoor()
{
	ProbType = EProbType::E_OneTimeProb;
	InteractionType = EInteractionType::E_OpenDoor;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat ActionTimeline;
		ActionTimeline.BindUFunction(this, "SetRotation");
		CurveTimeline.AddInterpFloat(CurveFloat, ActionTimeline);
		CurveTimeline.SetLooping(false);

		FOnTimelineEvent EndEventTrigger;
		EndEventTrigger.BindUFunction(this, "EndEvent");
		CurveTimeline.SetTimelineFinishedFunc(EndEventTrigger);

		StartRot = EndRot = GetActorRotation();
		EndRot.Yaw += YawOffset;
	}
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurveTimeline.IsPlaying())
	{
		CurveTimeline.TickTimeline(DeltaTime);
	}
}

void ADoor::SetRotation(float Value)
{
	FRotator NewRot = FMath::Lerp(StartRot, EndRot, Value);
	Body->SetWorldRotation(NewRot);
}

void ADoor::EndEvent()
{
	this->SetActorEnableCollision(true);
}

void ADoor::Active(ABaseHuman* human)
{
	Super::Active(human);

	// Active Door
	this->SetActorEnableCollision(false);

	if (bIsOpen) CurveTimeline.ReverseFromEnd();
	else CurveTimeline.PlayFromStart();

	bIsOpen = !bIsOpen;

	GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandle, this, &ADoor::AutoClose, 3.0f);
}

void ADoor::AutoClose()
{
	if (bIsOpen)
	{
		CurveTimeline.ReverseFromEnd();
		bIsOpen = !bIsOpen;
	}
}
