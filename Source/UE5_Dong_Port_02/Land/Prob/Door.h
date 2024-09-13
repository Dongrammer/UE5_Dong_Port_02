#pragma once

#include "CoreMinimal.h"
#include "BaseProb.h"
#include "Components/TimelineComponent.h"

#include "Door.generated.h"

class UCurveFloat;
class ANavLinkProxy;
class UNavLinkCustomComponent;

UCLASS()
class UE5_DONG_PORT_02_API ADoor : public ABaseProb
{
	GENERATED_BODY()
	
public:	
	ADoor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/* ========== Animation ==========*/
public:
	UFUNCTION()
	void SetRotation(float Value);
	UFUNCTION()
	void EndEvent();

private:
	FTimeline CurveTimeline;
	UPROPERTY(EditAnywhere, Category = "Timeline|Essential")
	UCurveFloat* CurveFloat;

	UPROPERTY()
	FRotator StartRot;
	UPROPERTY()
	FRotator EndRot;
	UPROPERTY(EditAnywhere, Category = "Timeline|Essential")
	float YawOffset;

	/* ========== Body ==========*/
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<USceneComponent> Architecture;

	/* ========== Activation ==========*/
public:
	void Active() override;
	FVector GetOutDoorLocation() { return ActiveMeshOut->GetComponentToWorld().GetLocation(); }
	FVector GetInDoorLocation() { return ActiveMeshIn->GetComponentToWorld().GetLocation(); }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	bool bIsOpen = false;

	/* ========== NPC ==========*/
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UChildActorComponent> NavLinkProxyChildActor;

public:
	UFUNCTION()
	void SmartLinkFunc(UNavLinkCustomComponent* SmartLink, UObject* PathComp, const FVector& DestPoint);
};
