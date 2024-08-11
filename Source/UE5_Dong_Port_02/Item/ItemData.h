#pragma once

#include "CoreMinimal.h"

#include "ItemData.generated.h"

class ABaseItem;

/* ==================== Base ==================== */
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
	E_Common UMETA(DisplayName = "Common"),
	E_Rare UMETA(DisplayName = "Rare"),
	E_Unique UMETA(DisplayName = "Unique"),
	E_Max
};

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
	TSubclassOf<ABaseItem> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	float Weight = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Other")
	FString Description;
};
// Item Class 넣어야하나?
/* ==================== Others ==================== */

UENUM(BlueprintType)
enum class EOtherEffect : uint8
{
	E_None UMETA(Hidden),
	E_HP UMETA(DisplayName = "HP"),
	E_MP UMETA(DisplayName = "MP"),
	E_Speed UMETA(DisplayName = "Speed")
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

/* ==================== Equipment ==================== */

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	E_None UMETA(Hidden),
	E_Head UMETA(DisplayName = "Head"),
	E_Chest UMETA(DisplayName = "Chest"),
	E_Legs UMETA(DisplayName = "Legs"),
	E_Feet UMETA(DisplayName = "Feet"),
	E_Hands UMETA(DisplayName = "Hands"),
	E_Weapon UMETA(DisplayName = "Weapon"),
	E_SubWeapon UMETA(DisplayName = "Weapon"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EEquipStatus : uint8
{
	E_None UMETA(Hidden),
	E_MHP UMETA(DisplayName = "MHP"),
	E_MMP UMETA(DisplayName = "MMP"),
	E_MSoul UMETA(DisplayName = "MSoul"),
	E_ATK UMETA(DisplayName = "ATK"),
	E_MATK UMETA(DisplayName = "MATK"),
	E_DEF UMETA(DisplayName = "DEF"),
	E_MDEF UMETA(DisplayName = "MDEF"),
	E_Critical UMETA(DisplayName = "Critical"),
	E_Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FEquipmentItem : public FItemDataTableBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	EEquipType EquipType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<EEquipStatus, int> EquipStatus;
};

/* ==================== Weapon ==================== */

UENUM(BlueprintType)
enum class EWeaponStatus : uint8
{
	E_None UMETA(Hidden),
	E_MHP UMETA(DisplayName = "MHP"),
	E_MMP UMETA(DisplayName = "MMP"),
	E_MSoul UMETA(DisplayName = "MSoul"),
	E_ATK UMETA(DisplayName = "ATK"),
	E_MATK UMETA(DisplayName = "MATK"),
	E_DEF UMETA(DisplayName = "DEF"),
	E_MDEF UMETA(DisplayName = "MDEF"),
	E_Critical UMETA(DisplayName = "Critical"),
	E_Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FWeaponItem : public FItemDataTableBase
{
	GENERATED_USTRUCT_BODY()

public:
};
