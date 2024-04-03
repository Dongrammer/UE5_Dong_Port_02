#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


struct FSlot
{
	FName Name;
};

UCLASS()
class UE5_DONG_PORT_02_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	TArray<FSlot> ItemSlots;

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter();
	virtual void SetCharacterMovement();
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
