#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Prob/Door.h"

#include "Building.generated.h"

//class ANPCHome_LocationVolume;

class UBoxComponent;
class USceneComponent;
class ABaseHuman;
class ABaseProb;

UCLASS()
class UE5_DONG_PORT_02_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	ABuilding();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/* ========== Body ==========*/
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<USceneComponent> Scene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<USceneComponent> Architecture;

	/* ========== Check In And Out ==========*/
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<UBoxComponent> InAndOutBox;
public:
	UFUNCTION()
	void ComeInCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void GetOutCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/* ========== Probs ==========*/
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Probs|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<ADoor> door;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Probs|Essential", meta = (AllowprivateAccess = "true"))
	TArray<TObjectPtr<ABaseProb>> Probs;

public:
	UFUNCTION()
	FVector GetOutDoorLocation();
	FVector GetInDoorLocation();
	void NPCActiveDoor();

	UFUNCTION()
	void GetOut(ABaseHuman* human);
	UFUNCTION()
	void GetIn(ABaseHuman* human);

public:
	template<typename T>
	TArray<TObjectPtr<T>> GetInsideProbs()
	{
		TArray<TObjectPtr<T>> temp;

		for (auto& p : Probs)
		{
			TObjectPtr<T> CastProb = Cast<T>(p);

			if (CastProb)
			{
				temp.Add(CastProb);
			}
		}

		return temp;
	}
};
