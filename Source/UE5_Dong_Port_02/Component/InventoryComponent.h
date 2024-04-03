#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseCharacter;
class UInventoryHUD;
/*
	아이템 리스트를 받아서 화면에 출력하는 컴포넌트
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

private:
	ABaseCharacter* Owner;
	APlayerController* OwnerController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryHUD> InvenHUDClass;

	UPROPERTY(VisibleDefaultsOnly)
	class UInventoryHUD* InvenHUD;
		
};
