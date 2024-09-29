#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeData.h"

DECLARE_LOG_CATEGORY_EXTERN(WorldContLog, Log, All);

#include "WorldController.generated.h"

class ADirectionalLight;
class UTPS_GameInstance;

UCLASS()
class UE5_DONG_PORT_02_API AWorldController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OneMinuteTimePass();

private:
	TObjectPtr<UTPS_GameInstance> GameInstance;

	/* ========== Day / Night ========== */
private:
	FGlobalTime GlobalTime;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "DayNight|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<ADirectionalLight> Sun;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "DayNight|Essential", meta = (AllowprivateAccess = "true"))
	TObjectPtr<ADirectionalLight> Moon;

	FRotator SunRotator;
	FRotator MoonRotator;

	UFUNCTION()
	void UpdateSun();

};
