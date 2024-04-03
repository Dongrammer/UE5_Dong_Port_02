#pragma once

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