#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

DECLARE_LOG_CATEGORY_EXTERN(DashActionLog, Log, All);

#include "BaseDash.generated.h"

class AHero;
enum class EInputDirection : uint8;

UCLASS()
class UE5_DONG_PORT_02_API ABaseDash : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseDash();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AHero> ActionOwner;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EInputDirection direction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DashDistance = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bActivation = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHolding = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanMove = true;

public:	
	virtual void Tick(float DeltaTime) override;

	void SettingOwner(TObjectPtr<AHero> InOwner);

	UFUNCTION()
	void PressedDash();
	UFUNCTION()
	void ReleasedDash();
	UFUNCTION(BlueprintCallable) // 아직 안쓰는 함수
	void SetLocation();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoDashMovement();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FVector StartLocation;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FVector EndLocation;

	FORCEINLINE float GetDashDistance() { return DashDistance; }
	FORCEINLINE bool GetActivation() { return bActivation; }
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EInputDirection ,TObjectPtr<UAnimMontage>> AnimAsset;
};
