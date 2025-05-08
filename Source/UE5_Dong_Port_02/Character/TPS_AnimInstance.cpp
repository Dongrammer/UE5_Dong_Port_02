#include "Character/TPS_AnimInstance.h"

#include "BaseHuman.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/WeaponComponent.h"

void UTPS_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseHuman>(TryGetPawnOwner());

	if (Owner != nullptr)
		Movement = Owner->GetCharacterMovement();
}

void UTPS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Movement || !Owner) return;

	bIsFalling = Movement->IsFalling();

	Velocity = Owner->GetVelocity();
	Speed = Velocity.Size2D();
	AnimSpeed = Owner->GetPlayRate();

	Rotation = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	Direction = CalculateDirection(Velocity, Rotation);

	if (Owner->GetWeaponComponent())
	{
		bWeaponHolding = Owner->GetWeaponHolding();
		WeaponType = Owner->GetWeaponComponent()->GetCurrentWeaponType();
	}
	//      ̰   ִ     Ǵ 
	bShouldMove = /*!FVector(0,0,0).Equals(Movement->GetCurrentAcceleration(), 0.5f) &&*/ Speed > 3.0f;
	bCanMove = Owner->GetCanMove();
	handleType = Owner->GetCurrentHandleType();
	SittingType = Owner->GetCurrentSittingType();
}
