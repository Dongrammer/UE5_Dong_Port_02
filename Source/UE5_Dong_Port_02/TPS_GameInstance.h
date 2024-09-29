#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Component/ItemComponent.h"
#include "Land/TimeData.h"

#include "TPS_GameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOneMinuteTimePass);

UCLASS()
class UE5_DONG_PORT_02_API UTPS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void OnStart() override;

	UItemComponent* GetItemComponent();

private:
	UPROPERTY()
	UItemComponent* ItemComponentInstance;

	/* ========== Global Time ========== */
public:
	void InitGlobalTime();
	UFUNCTION()
	void OneMinuteTimePass();
	UFUNCTION()
	FGlobalTime GetGlobalTime() { return GlobalTime; };

	FOneMinuteTimePass DOneMinuteTimePass;

	UFUNCTION()
	void SetTimeMult(float f);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowprivateAccess = "true"))
	float TimeMult = 5.0f;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowprivateAccess = "true"))
	FGlobalTime GlobalTime;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0", ClampMax = "24", AllowprivateAccess = "true"))
	//uint8 CurrentHour = 0; // 24 ~ 00
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0", ClampMax = "60", AllowprivateAccess = "true"))
	//uint8 CurrentMinute = 0; // 60 ~ 00
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0", AllowprivateAccess = "true"))
	//uint8 CurrentDay = 0;

	FTimerHandle SetGlobalTime;

};
