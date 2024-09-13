// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseVillage.generated.h"

class ANavModifierVolume;
class ABuilding;

UCLASS()
class UE5_DONG_PORT_02_API ABaseVillage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseVillage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* ========== Area ========== */
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TObjectPtr<ANavModifierVolume> VillageVolume;

	/* ========== Buildings ========== */
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<ABuilding>> Buildings;
};
