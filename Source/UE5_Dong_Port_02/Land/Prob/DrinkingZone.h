#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "DrinkingZone.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ADrinkingZone : public ABaseProb
{
	GENERATED_BODY()
	
protected:
	ADrinkingZone();

	void Active(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

	UFUNCTION()
	void PlayDrinkingAnims();
	UFUNCTION()
	void PlaySittingDrinkingAnims();

private:
	FTimerHandle DrinkingTHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	bool bSit = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> DrinkingAnims;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowprivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> SittingDrinkingAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TSubclassOf<ABaseItem> DrinkingCupClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowprivateAccess = "true"))
	TObjectPtr<ABaseItem> DrinkingCup;
};
