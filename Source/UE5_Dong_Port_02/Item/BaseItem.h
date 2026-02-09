#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "Components/SphereComponent.h"
#include "Helper.h"

DECLARE_LOG_CATEGORY_EXTERN(ItemLog, Log, All);
#include "BaseItem.generated.h"

class ABaseHuman;
class USphereComponent;
class UBoxComponent;
class UItemComponent;
//class UTextRenderComponent;

UCLASS()
class UE5_DONG_PORT_02_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	virtual void BeginPlay() override;
	virtual void DataTableSetting();

public:	
	virtual void Tick(float DeltaTime) override;

public:
	ABaseHuman* Owner;
	bool bInField = true;

protected:
	UPROPERTY()
	TObjectPtr<UItemComponent> ItemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Scene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> FixedPoint; // 캐릭터 소켓에 붙을 위치 기준점.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bTempItem = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	FItemData itemdata;
//
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	FName Name = "None";
};
