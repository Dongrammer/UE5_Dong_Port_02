#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "BaseOther.generated.h"

enum class EOtherEffect : uint8;
enum class ERarity : uint8;

USTRUCT(BlueprintType)
struct FOtherItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	ERarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	UTexture2D* Texture = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	UStaticMesh* StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	bool bCanUse = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	int MaxCount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	TMap<EOtherEffect, float> Effect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	UParticleSystem* EffectParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	float Weight = 0;
};

UCLASS()
class UE5_DONG_PORT_02_API ABaseOther : public ABaseItem
{
	GENERATED_BODY()

public:
	ABaseOther();
	virtual void BeginPlay() override;
	virtual void DataTableSetting() override;

private:
	bool bCanUse = false;
	int MaxCount = 1;

	UPROPERTY(VisibleAnywhere)
	TMap<EOtherEffect, float> Effect;
	UPROPERTY(VisibleAnywhere)
	float Duration;

	UPROPERTY(VisibleAnywhere)
	UParticleSystem* EffectParticle;
};
