#include "Land/Light/BaseLight.h"
#include "Helper.h"
#include "Components/PointLightComponent.h"

ABaseLight::ABaseLight()
{
	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	Body = Helper::CreateSceneComponent<USceneComponent>(this, "Body", Scene);
	PointLight = Helper::CreateSceneComponent<UPointLightComponent>(this, "PointLight", Scene);
}

void ABaseLight::BeginPlay()
{
	Super::BeginPlay();

	PointLight->SetHiddenInGame(true);
}

void ABaseLight::Active()
{
	PointLight->SetHiddenInGame(false);
}

void ABaseLight::Deactive()
{
	PointLight->SetHiddenInGame(true);
}

