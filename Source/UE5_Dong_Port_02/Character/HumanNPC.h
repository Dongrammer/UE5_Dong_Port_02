#pragma once

#include "CoreMinimal.h"
#include "Character/BaseHuman.h"

DECLARE_LOG_CATEGORY_EXTERN(HumanNPCLog, Log, All);

#include "HumanNPC.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API AHumanNPC : public ABaseHuman
{
	GENERATED_BODY()

public:
	AHumanNPC();

protected:
	void BeginPlay() override;
	void CreateCharacter() override;
};
