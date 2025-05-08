#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "../Weapon/WeaponData.h"
#include "../Item/ItemData.h"

#include "TPS_AnimInstance.generated.h"

//    漱  
class ABaseHuman;
class UCharacterMovementComponent;
enum class EHandleType : uint8;
enum class ESittingType : uint8;


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

	UPROPERTY(BlueprintReadWrite, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	// 움직이고 있는지 판단하는 변수
	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bWeaponHolding;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	bool bCanMove;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	EHandleType handleType;

	UPROPERTY(BlueprintReadOnly, Category = "BlendSpace", meta = (AllowPrivateAccess = "true"))
	ESittingType SittingType;

private:
	ABaseHuman* Owner;

	UCharacterMovementComponent* Movement;
	FRotator Rotation;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AnimSpeed = 1.0f;
};
