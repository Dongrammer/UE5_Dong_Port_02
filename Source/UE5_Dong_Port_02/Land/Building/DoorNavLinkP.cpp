#include "Land/Building/DoorNavLinkP.h"
#include "Land/Prob/Door.h"
#include "Character/BaseHuman.h"

ADoorNavLinkP::ADoorNavLinkP()
{
	PointLinks.Empty();
	SetSmartLinkEnabled(true);
	bSmartLinkIsRelevant = true;
}

void ADoorNavLinkP::BeginPlay()
{
	if (!Door)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Door Is NULL !!"), *this->GetFName().ToString());
		return;
	}

	FScriptDelegate SmartLinkDelegate;
	SmartLinkDelegate.BindUFunction(this, "OpenDoor");
	OnSmartLinkReached.Add(SmartLinkDelegate);
}

void ADoorNavLinkP::OpenDoor(AActor* MovingActor, const FVector& DestinationPoint)
{
	if (!Door->GetIsOpen())
	{
		TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(MovingActor);
		Door->Active(human);
	}
}
