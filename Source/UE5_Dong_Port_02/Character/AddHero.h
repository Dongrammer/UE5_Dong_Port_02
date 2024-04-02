#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AddHero.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;

UCLASS()
class UE5_DONG_PORT_02_API AAddHero : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAcces = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAcces = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAcces = "true"))
	UInputMappingContext* KeyMappingContext;

public:
	AAddHero();
	void Tick(float DeltaSecond) override;

	void CreateCharacter() override;

protected:
	void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void CreateCamera();
};
