#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "../Component/StatusComponent.h"

#include "HumanNPC/Widget/NPCHealthBar.h"

#include "../Land/TimeData.h"

#include "../Widget/Battle/DamageFloatingActor.h"

#include "BaseCharacter.generated.h"

class ABaseItem;
class UTPS_GameInstance;
class UWidgetComponent;
class UCameraComponent;

UCLASS()
class UE5_DONG_PORT_02_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter();
	virtual void SetCharacterMovement();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> BodyCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanMove = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StandardWalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStatusComponent> StatusComponent;

public:
	TObjectPtr<UCameraComponent> playerCamera;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool GetCanMove() { return bCanMove; }
	UFUNCTION()
	FORCEINLINE void SetCanMove(bool move) { bCanMove = move; }
	FORCEINLINE void SetCanAttack(bool attack) { bCanAttack = attack; }
	float GetCapsuleRadius();

	FORCEINLINE float GetStandardWalkSpeed() { return StandardWalkSpeed; }
	FORCEINLINE float GetCurrentSpeed() { return GetVelocity().Size2D(); }
	void SetWalkSpeed(float speed);
	void InitWalkSpeed();
	TObjectPtr<UStatusComponent> GetStatusComponent() { return StatusComponent; }
	void EQuipItemStatus(TMap<EEquipStatus, int> status) { StatusComponent->EquipItemStatus(status); }
	void UnequipItemStatus(TMap<EEquipStatus, int> status) { StatusComponent->UnequipItemStatus(status); }

	/* ==================== State ==================== */
public:
	UFUNCTION(BlueprintCallable)
	bool CurrentStateAre(TArray<EStateType> states) { return StatusComponent->CurrentStateAre(states); }
	UFUNCTION(BlueprintCallable)
	bool CurrentStateIs(EStateType state) { return StatusComponent->CurrentStateIs(state); }
	void SetCurrentState(EStateType state) { StatusComponent->SetCurrentState(state); }
	FORCEINLINE EStateType GetCurrentState() { return StatusComponent->GetCurrentState(); }
	void InitState();

	UFUNCTION()
	virtual void SetRagdoll();
	virtual void DeadRemove();
	FTimerHandle DeadTimer;

	/* ==================== EffectState ==================== */
public:
	UFUNCTION(BlueprintCallable)
	void SetEffectState(EStateEffectType type);

	UFUNCTION(BlueprintCallable)
	EStateEffectType GetEffectState() { return StatusComponent->GetCurrentEffectState(); }


	/* ==================== Battle ==================== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> HittedPoints;

public:
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamageFuc(AActor* damagecauser, int damage, FVector hittedlocation); // Pawn에 TakeDamage가 있기 때문에 Fuc을 붙임
	UFUNCTION(BlueprintCallable)
	virtual void TakeEffectDamageFuc(EStateEffectType type, int val);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ABaseCharacter> FightingCharacter;

	bool CurrentFighting = false;

public:
	TObjectPtr<ABaseCharacter> GetFighttingCharacter() { return FightingCharacter; }
	bool GetFighting() { return CurrentFighting; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential")
	TSubclassOf<ADamageFloatingActor> DamageFloatingWidgetClass;

	/* ==================== Time ==================== */
protected:
	TObjectPtr<UTPS_GameInstance> GameInstance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	FGlobalTime GlobalTime;

public:
	UFUNCTION()
	virtual void OneMinuteTimePass();

	/* ==================== Widget ==================== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UNPCHealthBar> HealthBarClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNPCHealthBar> HealthBar;

public:
	UFUNCTION()
	virtual void HealthBarVisible();
	UFUNCTION()
	void HealthBarInvisible();

	FTimerHandle HealthBarInvisibleHandle;

	/* ==================== Status ==================== */
public:
	UFUNCTION()
	void UpdateAttack(int val);
	UFUNCTION(BlueprintCallable)
	void GetEXP(int val);
	UFUNCTION(BlueprintCallable)
	void LevelUp();
};
