#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Helper.h"
#include "../../Character/BaseHuman.h"

DECLARE_LOG_CATEGORY_EXTERN(ProbLog, Log, All);

#include "BaseProb.generated.h"

class ABaseHuman;
class UAIPerceptionStimuliSourceComponent;

UENUM(BlueprintType)
enum class EProbType : uint8
{
	E_None UMETA(Hidden),
	E_WorkingProb UMETA(DisplayName = "Working Prob"),
	E_RestingProb UMETA(DisplayName = "Resting Prob"),
	E_OneTimeProb UMETA(DisplayName = "OneTime Prob"),
	E_Max UMETA(Hidden)
};

UCLASS()
class UE5_DONG_PORT_02_API ABaseProb : public AActor
{
	GENERATED_BODY()

public:
	ABaseProb();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	FName Name;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	//bool OneTimeProb = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	bool bCanPlayerUse = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	EProbType ProbType;

	// Rest Prob
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	ERestType RestType = ERestType::E_None;

	// Work Prob
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	EWorkType WorkType = EWorkType::E_None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Used = false;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseHuman> UsingHuman;

	// Interaction Prob
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	EInteractionType InteractionType = EInteractionType::E_None;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FName GetName() { return Name; }
	UFUNCTION()
	virtual bool GetUsed() { return Used; }
	TObjectPtr<ABaseHuman> GetUsingHuman() const { return UsingHuman; } 
	EWorkType GetWorkType() { return WorkType; }
	bool GetCanPlayerUse() { return bCanPlayerUse; }

	/* ========== Body ==========*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Scene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TObjectPtr<USceneComponent> Body;

	/* ========== Activation ==========*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ActiveMeshOut;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ActiveMeshIn;

public:
	UFUNCTION()
	virtual void Active(ABaseHuman* human);
	UFUNCTION()
	virtual void Deactive(ABaseHuman* human);
	UFUNCTION()
	virtual void PreActive(ABaseHuman* human);

	FVector GetActiveMeshInLocation() { return ActiveMeshIn->GetComponentLocation(); } // For NPC

	/* ========== Perception ==========*/
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionStimuliSourceComponent> StimulusSource;
};
