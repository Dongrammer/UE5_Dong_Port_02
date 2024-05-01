#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Weapon/WeaponData.h"

DECLARE_LOG_CATEGORY_EXTERN(ActionLog, Log, All);

#include "BaseAction.generated.h"

class ABaseCharacter;
class UAnimMontage;

UCLASS()
class UE5_DONG_PORT_02_API ABaseAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseAction();

protected:
	virtual void BeginPlay() override;

	TObjectPtr<ABaseCharacter> Owner;

public:	
	virtual void Tick(float DeltaTime) override;

	void SettingOwner(TObjectPtr<ABaseCharacter> InOwner);

public:
	void DoAction();

private:
	UPROPERTY(EditDefaultsOnly)
	EWeaponType ActionType;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseAction> ActionClass;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> AnimAsset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 ActionLevel = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> ActionImage;

public:
	FORCEINLINE EWeaponType GetActionType() { return ActionType; }
};
