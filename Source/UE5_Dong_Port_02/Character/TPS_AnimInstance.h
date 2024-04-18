#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPS_AnimInstance.generated.h"

// ���漱��
class ABaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class UE5_DONG_PORT_02_API UTPS_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	// ���� �����̰� �ִ��� �Ǵ��ϴ� ����
	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bWeaponHolding;

private:
	ABaseCharacter* Owner;

	UCharacterMovementComponent* Movement;
	FRotator Rotation;
};
