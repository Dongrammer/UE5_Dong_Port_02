#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeData.h"
#include "BaseVillage.generated.h"

class ANavModifierVolume;
class ABuilding;
class ABaseProb;
class ABaseLight;
class UTPS_GameInstance;
class AInn;
class AHumanNPC;

UCLASS()
class UE5_DONG_PORT_02_API ABaseVillage : public AActor
{
	GENERATED_BODY()

public:
	ABaseVillage();
	UFUNCTION()
	virtual void OneMinuteTimePass();

protected:
	virtual void BeginPlay() override;
	TObjectPtr<UTPS_GameInstance> GameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	FGlobalTime GlobalTime;

	/* ========== Area ========== */
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TObjectPtr<ANavModifierVolume> VillageVolume;

public:
	FVector GetRandomLocation();

	/* ========== Buildings ========== */
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<ABuilding>> Buildings;

public:
	TArray<TObjectPtr<AInn>> GetInns() const;

	/* ========== Probs ========== */
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<ABaseProb>> Probs;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<ABaseLight>> Lights;

public:
	template<typename T>
	TArray<TObjectPtr<T>> GetProbs()
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

public:
	TArray<TObjectPtr<ABaseProb>> GetAllProbs() { return Probs; }


	/* ========== NPC ========== */
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<AHumanNPC>> VillageNPCs;

public:
	void AddVillageNPC(AHumanNPC* npc);

	TArray<TObjectPtr<AHumanNPC>> GetAllVillageNPCs() { return VillageNPCs; }
};