#include "Land/WorldController.h"

#include "TPS_GameInstance.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"

DEFINE_LOG_CATEGORY(WorldContLog);

AWorldController::AWorldController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldController::BeginPlay()
{
	Super::BeginPlay();

	// Get Sun Rotator
	if (!Sun)
	{
		UE_LOG(WorldContLog, Warning, TEXT("Sun Is NULL !!"));
		return;
	}
	SunRotator = Sun->GetActorRotation();

	// Set Timer On GlobalTime
	GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());

	if (!GameInstance)
	{
		UE_LOG(WorldContLog, Warning, TEXT("GameInstance Is NULL !!"));
		return;
	}
	GameInstance->DOneMinuteTimePass.AddUFunction(this, "OneMinuteTimePass");

	// Get Moon Rotator
	if (!Moon)
	{
		UE_LOG(WorldContLog, Warning, TEXT("Moon Is NULL !!"));
		return;
	}
	//MoonRotator = SunRotator + FRotator(180, 180, 180);s
	//Moon->AttachToActor(Sun, FAttachmentTransformRules::KeepRelativeTransform);
	//Moon->SetActorRotation(SunRotator + FRotator(0, 180.0f, 0));
	Moon->SetActorRotation(SunRotator + FRotator(180, 0, 0));
}

// Called every frame
void AWorldController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldController::OneMinuteTimePass()
{
	GlobalTime = GameInstance->GetGlobalTime();
	UpdateSun();
}

void AWorldController::UpdateSun()
{
	float CurTime = GlobalTime.CurrentTime;

	//FRotator ro = Sun->GetActorRotation();
	//ro.Pitch = ((360.0f / 1440.0f) * CurTime);
	//FQuat qu = FQuat(ro);
	//ro.Pitch += 1;
	/*if (CurTime > 1080) ro.Pitch -= 360.0f;
	else ro.Pitch += 180.0f;*/
	SunRotator.Pitch = ((360.0f / 1440.0f) * CurTime) + 60;
	//SunRotator.Pitch = ((360.0f / 1440.0f) * CurTime) - 90;

	Sun->SetActorRotation(SunRotator);
	//UE_LOG(LogTemp, Log, TEXT("%0.2f, %0.2f, %0.2f"),ro.Roll ,ro.Pitch, ro.Yaw);
}

