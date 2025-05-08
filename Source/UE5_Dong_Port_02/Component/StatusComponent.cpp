#include "Component/StatusComponent.h"

#include "../Character/BaseCharacter.h"
#include "Widget/Status/StatusHUD.h"

DEFINE_LOG_CATEGORY(StatusCompLog);

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	UpExpList.Init(100, 100);
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	if (!OwnerCharacter)
	{
		UE_LOG(StatusCompLog, Warning, TEXT("OwnerCharacter Is NULL !!"));
	}

	CombineStatus();
	InitStatus();
}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatusComponent::InitStatusHUD(TObjectPtr<UStatusHUD> hud)
{
	StatusHUD = hud;
	StatusHUD->SetVisibility(ESlateVisibility::Hidden);

	CombineStatus();
	InitStatus();
}


bool UStatusComponent::CurrentStateAre(TArray<EStateType> states)
{
	for (EStateType st : states)
	{
		if (CurrentState == st)
			return true;
	}

	return false;
}

bool UStatusComponent::CurrentStateIs(EStateType state)
{
	if (CurrentState == state)
		return true;
	else
		return false;
}

void UStatusComponent::SetCurrentEffectState(EStateEffectType type)
{
	CurrentEffectState = type;

	if (StatusHUD)
	{
		StatusHUD->UpdateEffectState(type);
	}
}

void UStatusComponent::CombineStatus()
{
	TotalStatus.MHP = CharacterStatus.MHP + EquipStatus.MHP;
}

void UStatusComponent::InitStatus()
{
	TotalStatus.HP = TotalStatus.MHP;

	// Player HUD
	UpdateStatusHUD();
}

void UStatusComponent::UpdateStatusHUD()
{
	if (!StatusHUD) return;

	StatusHUD->UpdateHP(TotalStatus.MHP, TotalStatus.HP);
	StatusHUD->UpdateLevel(Level);
	UpExp = UpExpList[Level - 1];
	StatusHUD->UpdateEXP(Exp, UpExp);
}

void UStatusComponent::UpdateHP(int val)
{
	TotalStatus.HP -= val;

	// Player HUD
	if (StatusHUD)
	{
		StatusHUD->UpdateHP(TotalStatus.MHP, TotalStatus.HP);
	}

	if (TotalStatus.HP <= 0)
	{
		SetCurrentState(EStateType::E_Dead);
	}
}

void UStatusComponent::UpdateAttack(int val)
{
	TotalStatus.ATK += val;

	if (StatusHUD)
	{
		StatusHUD->UpdateAttack(TotalStatus.ATK);
	}
}

void UStatusComponent::GetEXP(int val)
{
	if (Level >= MaxLevel) return;

	Exp += val;

	if (Exp >= UpExp)
	{
		LevelUp();
	}

	// Player HUD
	if (StatusHUD)
	{
		StatusHUD->UpdateEXP(Exp, UpExp);
	}
}

void UStatusComponent::LevelUp()
{
	if (Level >= MaxLevel) return;

	if (Exp - UpExp < 0)
	{
		Exp = 0;
	}
	else
	{
		Exp -= UpExp;
	}
	Level++;

	if (Level >= MaxLevel)
	{
		UpExp = 0;
	}
	else
	{
		UpExp = UpExpList[Level - 1];
	}

	// Player HUD
	if (StatusHUD)
	{
		StatusHUD->UpdateLevel(Level);
		StatusHUD->UpdateEXP(Exp, UpExp);
	}
}

void UStatusComponent::EquipItemStatus(TMap<EEquipStatus, int> status)
{
	EquipStatus.MHP += status.FindRef(EEquipStatus::E_MHP);
	EquipStatus.ATK += status.FindRef(EEquipStatus::E_ATK);

	// Player HUD
	CombineStatus();
	UpdateStatusHUD();
}

void UStatusComponent::UnequipItemStatus(TMap<EEquipStatus, int> status)
{
	EquipStatus.MHP -= status.FindRef(EEquipStatus::E_MHP);
	EquipStatus.ATK -= status.FindRef(EEquipStatus::E_ATK);

	// Player HUD
	CombineStatus();
	UpdateStatusHUD();
}
