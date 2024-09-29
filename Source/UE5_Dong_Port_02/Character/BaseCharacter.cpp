#include "BaseCharacter.h"

<<<<<<< HEAD
#include "TPS_GameInstance.h"
=======
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
>>>>>>> parent of 61cfc84 (~2024/09/14 Update)

//#include "Component/ItemComponent.h"
#include "Item/BaseItem.h"
#include "Helper.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = GetCapsuleComponent();
	SetCharacterMovement();

	StatusComponent = Helper::CreateActorComponent<UStatusComponent>(this, "Status Component");
	//ItemComponent = Helper::CreateActorComponent<UItemComponent>(this, "Item Component");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::CreateCharacter()
{
}

void ABaseCharacter::SetCharacterMovement()
{
	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = true;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 600.0f;
	StandardWalkSpeed = Comp->MaxWalkSpeed;

	// 멈췄을 때 감속
	Comp->BrakingDecelerationWalking = 2000.0f;
	// 떨어질 때 감속
	Comp->BrakingDecelerationFalling = 1500.0f;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::GetCapsuleRadius()
{
	return BodyCollision->GetScaledCapsuleRadius();
}

void ABaseCharacter::SetWalkSpeed(float speed)
{
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void ABaseCharacter::InitWalkSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = StandardWalkSpeed;
}
