#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABaseItem;
class UItemComponent;

UCLASS()
class UE5_DONG_PORT_02_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter();
	virtual void SetCharacterMovement();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> BodyCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanMove = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StandardWalkSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE bool GetCanMove() { return bCanMove; }
	UFUNCTION()
	FORCEINLINE void SetCanMove(bool move) { bCanMove = move; }
	FORCEINLINE void SetCanAttack(bool attack) { bCanAttack = attack; }
	float GetCapsuleRadius();

	FORCEINLINE float GetStandardWalkSpeed() { return StandardWalkSpeed; }
	void SetWalkSpeed(float speed);	
	void InitWalkSpeed();
};
