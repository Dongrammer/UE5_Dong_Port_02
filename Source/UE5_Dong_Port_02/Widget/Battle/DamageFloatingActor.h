#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageFloatingActor.generated.h"

class UWidgetComponent;
class UDamageFloating;

UCLASS()
class UE5_DONG_PORT_02_API ADamageFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageFloatingActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DamageFloatingClass;

public:	
	virtual void Tick(float DeltaTime) override;

	void ActiveWidget(float damage);
	UFUNCTION()
	void DestroySelf();
};
