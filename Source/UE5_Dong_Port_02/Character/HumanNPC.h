#pragma once

#include "CoreMinimal.h"
#include "Character/BaseHuman.h"
#include "BehaviorTree/BehaviorTree.h"

// #include "../Land/Trigger/Home/NPCHome_LocationVolume.h"
#include "../Land/Building/Building.h"
#include "../Land/BaseVillage.h"

DECLARE_LOG_CATEGORY_EXTERN(HumanNPCLog, Log, All);

#include "HumanNPC.generated.h"

class ANPCHome_LocationVolume;
class ABaseProb;

UENUM(BlueprintType)
enum class ERoutineType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_GoWork UMETA(DisplayName = "Go Work"),
	E_GoHome UMETA(DisplayName = "Go Home"),
	E_DoHobby UMETA(DisplayName = "Do Hobby"),
	E_Sleep UMETA(DisplayName = "Sleep"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EJobType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Blacksmith UMETA(DisplayName = "Blacksmith"),
	E_Guard UMETA(DisplayName = "Guard"),
	E_ShopKeeper UMETA(DisplayName = "ShopKeeper"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHobbies : uint8
{
	E_None UMETA(Hidden),
	E_RestAtHome UMETA(DisplayName = "Rest At Home"),
	E_Cooking UMETA(DisplayName = "Cooking"),
	E_MeetingSomeone UMETA(DisplayName = "Meeting SomeOne"),
	E_Drinking UMETA(DisplayName = "Drinking"),
	E_Walk UMETA(DisplayName = "Walk"),
	E_Max UMETA(Hidden)
};

UCLASS()
class UE5_DONG_PORT_02_API AHumanNPC : public ABaseHuman
{
	GENERATED_BODY()

public:
	AHumanNPC();

	TObjectPtr<UBehaviorTree> GetBehaviorTree() const { return BehaviorTree; }
	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;
	void CreateCharacter() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual void OneMinuteTimePass() override;

	/* ========== Pushed ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> PushedCapsule;

	TArray<TObjectPtr<ABaseHuman>> OverlapHuman;



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
	TMap<ERoutineType, FGlobalTime> Routines; // 루틴은 " ~시 : ~분 부터 루틴을 실행"

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Daily", meta = (AllowprivateAccess = "true"))
	ERoutineType CurrentRoutine;
	void SortRoutines();

public:
	UFUNCTION()
	TMap<ERoutineType, FGlobalTime> GetRoutines() const { return Routines; }
	void SetCurrentRoutine(ERoutineType type) { CurrentRoutine = type; }
	ERoutineType GetCurrentRoutine() { return CurrentRoutine; }

	/* ========== Job ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Job|Essential", meta = (AllowprivateAccess = "true"))
	TArray<EJobType> Jobs;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Job", meta = (AllowprivateAccess = "true"))
	TArray<TObjectPtr<ABaseProb>> WorkProbs;

public:
	void SetWorkProb();
	TArray<TObjectPtr<ABaseProb>> GetWorkProbs() { return WorkProbs; }
	TArray<EJobType> GetJobs() { return Jobs; }

	void StartWork(EWorkType type) override;
	void StopWork() override;

	/* ========== Hobbies ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hobbies|Essential", meta = (AllowprivateAccess = "true"))
	TMap<EHobbies, uint8> Hobbies; // 종류 / 확률
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hobbies", meta = (AllowprivateAccess = "true"))
	EHobbies CurrentHobby = EHobbies::E_None;

public:
	void SetRandomHobby();
	UFUNCTION()
	EHobbies GetCurrentHobby() { return CurrentHobby; }

	/* ========== Condition ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition", meta = (AllowprivateAccess = "true"), meta = (ClampMin = 0))
	int MaxFatigue = 1000; // 최대 피로도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition", meta = (AllowprivateAccess = "true"), meta = (ClampMin = 0))
	int CurrentFatigue = 0;
	int FatigueValue = 1; // 피로도 증가량 = 직업에 따라 다름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition", meta = (AllowprivateAccess = "true"), meta = (ClampMin = 0), meta = (ClampMax = 100))
	uint8 Endurance = 0; // 인내력 (퍼센트)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition", meta = (AllowprivateAccess = "true"))
	int RecoveryFatigueValue = 1; // 자연 회복 피로도

	FTimerHandle ConditionTimerHandle;
public:
	bool CheckOverFatique() { return MaxFatigue <= CurrentFatigue; }
	UFUNCTION()
	int GetCurrentFatigue() { return CurrentFatigue; }
	UFUNCTION()
	void InitCondition();
	UFUNCTION()
	void UpdateCondition();
	UFUNCTION()
	void RecoveryFatigue(uint8 percent);

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNPCHealthBar> HealthBar;*/

	/* ========== Action ========== */
public:
	void EndActionNotify() override;


	/* ========== Player ========== */
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowprivateAccess = "true"))
	int Likeability = 0;

public:
	UFUNCTION()
	void Increasedlikeability(int n);
	UFUNCTION()
	void Decreasedlikeability(int n);

	/* ========== Battle ========== */
public:
	virtual void TakeDamageFuc(AActor* damagecauser, int damage, FVector hittedlocation) override;
};
