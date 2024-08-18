#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(SoulCompLog, Log, All);

#include "SoulComponent.generated.h"

class AHero;
class USoulHUD;
class UNiagaraSystem;
class UNiagaraComponent;
class UCameraShakeBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API USoulComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USoulComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHero> OwnerCharacter;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> PlayerController;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (clampmin = "0"), meta = (AllowPrivateAccess = "true"))
	float MaxSoulGage = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (clampmin = "0"), meta = (AllowPrivateAccess = "true"))
	float CurrentSoulGage = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RecoveryGage = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 MaxSoulLevel = 3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 SoulLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoulHUD> SoulHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TSubclassOf<USoulHUD> SoulHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TObjectPtr<UAnimMontage> SoulBurnAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TArray<TObjectPtr<UNiagaraSystem>> NS_SoulBurnTrail;
	TObjectPtr<UNiagaraComponent> TrailComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TObjectPtr<UNiagaraSystem> NS_SoulBurnExplosion;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TSubclassOf<UCameraShakeBase> CS_SoulBurn;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SoulBurn();
	UFUNCTION()
	void SetSoulGage();
	UFUNCTION()
	void NiagaraSetting();
	UFUNCTION()
	void SoulRecovery();

	FTimerHandle SetGageTimer;
	FTimerHandle RecoveryTimer;
};
