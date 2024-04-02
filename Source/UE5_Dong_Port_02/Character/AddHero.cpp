#include "Character/AddHero.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Helper.h"

AAddHero::AAddHero()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	CreateCharacter();
	CreateCamera();
}

void AAddHero::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AAddHero::CreateCharacter()
{
	Super::CreateCharacter();
}

void AAddHero::BeginPlay()
{
	Super::BeginPlay();
}

void AAddHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAddHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 300.0f;
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetRelativeLocation(FVector(0, 30, 150));

	Camera = Helper::CreateSceneComponent<UCameraComponent>(this, "Camera", CameraArm);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeRotation(FRotator(-10, 0, 0));
}
