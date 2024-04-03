#include "Character/TPS_AnimInstance.h"

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPS_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseCharacter>(TryGetPawnOwner());

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

	Rotation = FRotator(0, Owner->GetControlRotation().Yaw, 0);
	Direction = CalculateDirection(Velocity, Rotation);

	// 움직이고 있는지 판단
	bShouldMove = /*!FVector(0,0,0).Equals(Movement->GetCurrentAcceleration(), 0.5f) &&*/ Speed > 3.0f;
}
