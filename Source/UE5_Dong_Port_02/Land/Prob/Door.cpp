#include "Land/Prob/Door.h"

#include "Components/SceneComponent.h"
#include "Navigation/NavLinkProxy.h"
#include "NavLinkCustomComponent.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	 
	Architecture = Helper::CreateSceneComponent<USceneComponent>(this, "Architecture", Scene);
	//NavLink = Helper::CreateSceneComponent<ANavLinkProxy>(this, "NavLink", Scene);
	NavLinkProxyChildActor = Helper::CreateSceneComponent<UChildActorComponent>(this, "NavLink", Scene);
	NavLinkProxyChildActor->SetChildActorClass(ANavLinkProxy::StaticClass());

	TObjectPtr<ANavLinkProxy> NavLink = Cast<ANavLinkProxy>(NavLinkProxyChildActor->GetChildActor());
	if (!NavLink)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting to ANavLinkProxy Fail !!"));
		return;
	}
	NavLink->PointLinks.Empty();
	NavLink->SetSmartLinkEnabled(true);
	TObjectPtr<UNavLinkCustomComponent> SmartLink = NavLink->GetSmartLinkComp();
	if (SmartLink)
	{
		FVector Start = GetActorLocation() + FVector(0, 100, 20);
		FVector End = GetActorLocation() + FVector(0, -100, 20);
		SmartLink->SetLinkData(Start, End, ENavLinkDirection::BothWays);
	}
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

	TObjectPtr<ANavLinkProxy> NavLink = Cast<ANavLinkProxy>(NavLinkProxyChildActor->GetChildActor());
	if (!NavLink)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting to ANavLinkProxy Fail !!"));
		return;
	}
	NavLink->PointLinks.Empty();
	NavLink->SetSmartLinkEnabled(true);
	TObjectPtr<UNavLinkCustomComponent> SmartLink = NavLink->GetSmartLinkComp();
	if (SmartLink)
	{
		FVector Start = GetActorLocation() + FVector(0, 100, 20);
		FVector End = GetActorLocation() + FVector(0, -100, 20);
		SmartLink->SetLinkData(Start, End, ENavLinkDirection::BothWays);
		
		SmartLink->SetMoveReachedLink(this, &ADoor::SmartLinkFunc);
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
	Architecture->SetWorldRotation(NewRot);
}

void ADoor::EndEvent()
{
	this->SetActorEnableCollision(true);
}

void ADoor::Active()
{
	this->SetActorEnableCollision(false);

	if (bIsOpen) CurveTimeline.ReverseFromEnd();
	else CurveTimeline.PlayFromStart();

	bIsOpen = !bIsOpen;
}

void ADoor::SmartLinkFunc(UNavLinkCustomComponent* SmartLink, UObject* PathComp, const FVector& DestPoint)
{
	UE_LOG(LogTemp, Log, TEXT("!!!"));
}
