#pragma once

#include "CoreMinimal.h"
#include "Character/BaseHuman.h"
#include "BehaviorTree/BehaviorTree.h"

#include "../Land/Trigger/Home/NPCHome_LocationVolume.h"
#include "../Land/Building/Building.h"
#include "../Land/BaseVillage.h"

DECLARE_LOG_CATEGORY_EXTERN(HumanNPCLog, Log, All);

#include "HumanNPC.generated.h"

class ANPCHome_LocationVolume;

UENUM(BlueprintType)
enum class ERoutineType : uint8
{
	E_None UMETA(Hidden),
	E_GoWork UMETA(DisplayName = "Go Work"),
	E_GoHome UMETA(DisplayName = "Go Home"),
	E_Max
};

UENUM(BlueprintType)
enum class EJobType : uint8
{
	E_None UMETA(Hidden),
	E_Blacksmith UMETA(DisplayName = "Blacksmith"),
	E_Guard UMETA(DisplayName = "Guard"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHobbies : uint8
{
	E_None UMETA(Hidden),
	E_RestAtHome UMETA(DisplayName = "Rest At Home"),
	E_Cooking UMETA(DisplayName = "Cooking"),
	E_MeetingSomeone UMETA(DisplayName = "Meeting SomeOne"),
	E_Max UMETA(Hidden)
};

UCLASS()
class UE5_DONG_PORT_02_API AHumanNPC : public ABaseHuman
{
	GENERATED_BODY()

public:
	AHumanNPC();

	TObjectPtr<UBehaviorTree> GetBehaviorTree() const { return BehaviorTree; }

protected:
	void BeginPlay() override;
	void CreateCharacter() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;


	/* ========== Home ========== */
public:
	FVector GetHomeLocation();
	TObjectPtr<ABuilding> GetHome() { return Home; }
	TObjectPtr<ABaseVillage> GetVillage() { return AffiliatedVillage; }

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Home|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<ABuilding> Home;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Home|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<ABaseVillage> AffiliatedVillage;

	/* ========== Daily Routine ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Daily|Essential", meta = (AllowprivateAccess = "true"))
	TMap<ERoutineType, FGlobalTime> Routines; // 루틴은 " ~시 : ~분 까지 루틴을 실행"

	//void SortRoutines();

public:
	UFUNCTION()
	TMap<ERoutineType, FGlobalTime> GetRoutines() const { return Routines; }

	/* ========== Job ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Job|Essential", meta = (AllowprivateAccess = "true"))
	EJobType Job;

	/* ========== Hobbies ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hobbies|Essential", meta = (AllowprivateAccess = "true"))
	TMap<EHobbies, uint8> Hobbies;
};
