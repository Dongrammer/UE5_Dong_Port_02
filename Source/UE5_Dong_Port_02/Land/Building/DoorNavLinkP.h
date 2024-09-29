#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "DoorNavLinkP.generated.h"

class ADoor;

UCLASS()
class UE5_DONG_PORT_02_API ADoorNavLinkP : public ANavLinkProxy
{
	GENERATED_BODY()
	
public:
	ADoorNavLinkP();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OpenDoor(AActor* MovingActor, const FVector& DestinationPoint);

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Essential")
	TObjectPtr<ADoor> Door;
};
