#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
DECLARE_LOG_CATEGORY_EXTERN(ItemLog, Log, All);
#include "BaseItem.generated.h"

enum class EItemType : uint8;
enum class ERarity : uint8;
class ABaseCharacter;
class USphereComponent;

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

protected:
	ABaseCharacter* Owner;

protected:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

public:
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* DataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	EItemType ItemType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	FName ItemID = "";

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
};
