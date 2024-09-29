#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "Anvil.generated.h"

/**
 *
 */
UCLASS()
class UE5_DONG_PORT_02_API AAnvil : public ABaseProb
{
	GENERATED_BODY()

public:
	AAnvil();

	void Active(ABaseHuman* human) override;
};
