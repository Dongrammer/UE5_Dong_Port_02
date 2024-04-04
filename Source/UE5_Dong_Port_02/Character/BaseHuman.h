#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BaseHuman.generated.h"

class UInventoryComponent;
class ABaseItem;
/**
 * 
 */
UCLASS()
class UE5_DONG_PORT_02_API ABaseHuman : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseHuman();

	bool Interaction = false;
	UFUNCTION()
	virtual void GetItems(ABaseItem* item, int count);
	virtual bool CheckItemWeight(float itemweight);

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter() override;
	virtual void SetCharacterMovement() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryComponent> InventoryComponent;
};
