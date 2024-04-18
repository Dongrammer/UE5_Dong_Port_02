#include "Component/SoulComponent.h"

USoulComponent::USoulComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USoulComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void USoulComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

