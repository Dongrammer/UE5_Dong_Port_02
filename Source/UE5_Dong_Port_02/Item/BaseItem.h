#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
DECLARE_LOG_CATEGORY_EXTERN(ItemLog, Log, All);
#include "BaseItem.generated.h"

class ABaseHuman;
class USphereComponent;
class UBoxComponent;
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
	//virtual void TextSetting();

public:	
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//virtual void TextOnOff();

public:
	ABaseHuman* Owner;
	// ABaseHuman* AccessPlayer;
	bool bInField = true;

protected:
	//UPROPERTY(EditDefaultsOnly)
	//USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTextRenderComponent> Text;*/

public:
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* DataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	FItemData itemdata;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	FName Name = "None";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	ERarity Rarity;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UTexture2D* Texture = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UStaticMesh* ItemSM = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	FString Description = "";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	float Weight = 0;
	//UPROPERTY(VisibleAnywhere, Category = "DataTable")
	//TObjectPtr<ABaseItem> ItemClass;
};
