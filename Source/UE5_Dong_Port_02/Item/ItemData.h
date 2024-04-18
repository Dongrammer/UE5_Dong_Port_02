#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	E_None UMETA(Hidden),
	E_Equipment UMETA(DisplayName = "Equip"),
	E_Weapon UMETA(DisplayName = "Weapon"),
	E_SoulWeapon UMETA(DisplayName = "Soul Weapon"),
	E_Other UMETA(DisplayName = "Other"),
	E_Max
};

UENUM(BlueprintType)
enum class ERarity : uint8
{
	E_None UMETA(Hidden),
	E_Common UMETA(DiplayName = "Common"),
	E_Rare UMETA(DiplayName = "Rare"),
	E_Unique UMETA(DiplayName = "Unique"),
	E_Max
};

UENUM(BlueprintType)
enum class EOtherEffect : uint8
{
	E_None UMETA(Hidden),
	E_HP UMETA(DisplayName = "HP"),
	E_MP UMETA(DisplayName = "MP"),
	E_Speed UMETA(DisplayName = "Speed")
};

// Inventory�� �� ������
USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	EItemType ItemType = EItemType::E_None;

	UPROPERTY(EditAnywhere, BlueprintreadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	FName ItemID = "";
};

USTRUCT(BlueprintType)
struct FItemDataTableBase : public FTableRowBase
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
	float Weight = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	FString Description;
};

USTRUCT(BlueprintType)
struct FEquipmentItem : public FItemDataTableBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	UParticleSystem* Particle;
};

USTRUCT(BlueprintType)
struct FOtherItem : public FItemDataTableBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	bool bCanUse = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	TMap<EOtherEffect, float> Effect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	UParticleSystem* EffectParticle;
};