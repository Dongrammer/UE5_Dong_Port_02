#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLight.generated.h"

class UPointLightComponent;

UCLASS()
class UE5_DONG_PORT_02_API ABaseLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseLight();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Scene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Body;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPointLightComponent> PointLight;

protected:
	virtual void BeginPlay() override;

public:

	virtual void Active();
	virtual void Deactive();
};
