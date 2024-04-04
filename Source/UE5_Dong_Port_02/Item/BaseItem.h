#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
DECLARE_LOG_CATEGORY_EXTERN(ItemLog, Log, All);
#include "BaseItem.generated.h"

enum class EItemType : uint8;
enum class ERarity : uint8;
class ABaseHuman;
class USphereComponent;
class UTextRenderComponent;

// Inventory에 들어갈 데이터
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	FName ItemID = "";
};

UCLASS()
class UE5_DONG_PORT_02_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

protected:
	virtual void BeginPlay() override;
	virtual void DataTableSetting();
	virtual void TextSetting();

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void TextOnOff();

public:
	ABaseHuman* Owner;
	ABaseHuman* AccessPlayer;

protected:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTextRenderComponent> Text;

public:
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* DataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	FItemData itemdata;

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
};
