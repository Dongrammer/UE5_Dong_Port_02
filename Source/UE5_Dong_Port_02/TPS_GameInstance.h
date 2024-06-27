#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Component/ItemComponent.h"

#include "TPS_GameInstance.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UTPS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UItemComponent* GetItemComponent();

private:
	UPROPERTY()
	UItemComponent* ItemComponentInstance;
};
