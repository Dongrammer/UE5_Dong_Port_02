#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Helper.h"

#include "BaseProb.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ABaseProb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* ========== Body ==========*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Scene;

	/* ========== Activation ==========*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ActiveMeshOut;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ActiveMeshIn;

public:
	virtual void Active();
};
