#include "Component/ActionComponent.h"

#include "Action/ActionDataAsset.h"
#include "Action/BaseAction.h"
#include "Action/BaseDash.h"

#include "../Character/Hero.h"
#include "../Character/BaseCharacter.h"
#include "Helper.h"

DEFINE_LOG_CATEGORY(ActionCompLog);

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ActionDataAsset = Helper::GetAsset<UActionDataAsset>(L"/Game/Actions/DA_Action");

	// Init SelectAction 
	FActionArray TempArray;
	TempArray.Actions.Init(nullptr, 5);

	for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
	{
		SelectActions.Add(static_cast<EWeaponType>(i), TempArray);
	}
	//
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<AHero>(GetOwner());

	// Check Safe
	if (!Owner) 
	{ 
		UE_LOG(ActionCompLog, Warning, TEXT("Owner Is NULL !!")); 
		return; 
	}

	// 
	CreateActions();
}

void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UActionComponent::SettingActions(TArray<FActionData> actions)
{
	for (int i = 0; i < actions.Num(); i++)
	{
		switch (actions[i].ActionType)
		{
		case EActionType::E_Gauntlet:
		{
			SelectActions.Find(static_cast<EWeaponType>(static_cast<uint8>(actions[i].ActionType)))->Actions[i] = GauntletActionPtr.FindRef(static_cast<EGauntletAction>(actions[i].ActionNumber));
			break;
		}
		case EActionType::E_OneHandSword:
		{
			SelectActions.Find(static_cast<EWeaponType>(static_cast<uint8>(actions[i].ActionType)))->Actions[i] = SwordActionPtr.FindRef(static_cast<ESwordAction>(actions[i].ActionNumber));
			break;
		}
		default:
		{
			//SelectActions.Find(static_cast<EWeaponType>(static_cast<uint8>(actions[i].ActionType)))->Actions[i] = nullptr;
			break;
		}
		/*case EActionType::E_None:
		{
			UE_LOG(LogTemp, Warning, TEXT("ActionComponent : Setting Action Type Is NULL !!"));
			break;
		}*/
		}
	}
}

void UActionComponent::CreateActions()
{
	for (auto& AcData : ActionDataAsset->Dash_Actions)
	{
		TObjectPtr<ABaseDash> action = GetWorld()->SpawnActor<ABaseDash>(AcData.Value);
		DashActionPtr.Add(AcData.Key, action);
		action->SettingOwner(Cast<AHero>(GetOwner()));
	}

	for (auto& AcData : ActionDataAsset->Gauntlet_Actions)
	{
		TObjectPtr<ABaseAction> action = GetWorld()->SpawnActor<ABaseAction>(AcData.Value);
		GauntletActionPtr.Add(AcData.Key, action);
		action->SettingOwner(Cast<AHero>(GetOwner()));
	}

	for (auto& AcData : ActionDataAsset->Sword_Actions)
	{
		TObjectPtr<ABaseAction> action = GetWorld()->SpawnActor<ABaseAction>(AcData.Value);
		SwordActionPtr.Add(AcData.Key, action);
		action->SettingOwner(Cast<AHero>(GetOwner()));
	}
}

void UActionComponent::PassiveLevelUp(FActionData InAction, EActionPassiveType Ptype)
{
	TObjectPtr<ABaseAction> action;

	switch (InAction.ActionType)
	{
	case EActionType::E_Gauntlet:
	{
		action = GauntletActionPtr.FindRef(static_cast<EGauntletAction>(InAction.ActionNumber));
		break;
	}
	case EActionType::E_OneHandSword:
	{
		action = SwordActionPtr.FindRef(static_cast<ESwordAction>(InAction.ActionNumber));
		break;
	}
	default:
	{
		UE_LOG(ActionCompLog, Warning, TEXT("PassiveLevelUp : ActionType Is NULL !!"));
		break;
	}
	}

	switch (Ptype)
	{
	case EActionPassiveType::E_SpeedUp:
	{
		action->PassiveSpeedUp();
		break;
	}
	default:
		break;
	}
}

void UActionComponent::DoAction()
{
	TArray<TObjectPtr<ABaseAction>> actions = SelectActions.Find(CurrentWeaponType)->Actions;

	// Check Safe
	/*if (!SelectActions[0]) return;
	if (!SelectActions[MontageIndex]) MontageIndex = 0;*/
	if (!actions[0]) return;
	if (!actions[MontageIndex]) MontageIndex = 0;

	// Set CanMove
	//if (SelectActions[MontageIndex]->GetCanMove() == false) Owner->SetCanMove(false);
	if (actions[MontageIndex]->GetCanMove() == false) Owner->SetCanMove(false);
	else Owner->SetCanMove(true); // Can't Move Attack -> Can Move Attack 으로 넘어갈 때 필요

	// Set CanAttack
	Owner->SetCanAttack(false);
	Owner->SetCurrentState(EStateType::E_Attack);

	/*if (SelectActions[MontageIndex]->GetCanMove() == false)
		Owner->bUseControllerRotationYaw = false;
	else
		Owner->bUseControllerRotationYaw = true;*/

	if (actions[MontageIndex]->GetCanMove() == false)
		Owner->bUseControllerRotationYaw = false;
	else
		Owner->bUseControllerRotationYaw = true;

	// Do Action
	/*SelectActions[MontageIndex]->DoAction();
	NowAction = SelectActions[MontageIndex];*/
	actions[MontageIndex]->DoAction();
	NowAction = actions[MontageIndex];

	MontageIndex++;
}

void UActionComponent::EndAction()
{
}

void UActionComponent::OnEndActionNotify()
{
	if (MontageIndex >= 5) MontageIndex = 0;

	if (bNextAction)
	{
		DoAction();
		bNextAction = false;
		return;
	}

	NowAction = nullptr;
	MontageIndex = 0;
	Owner->InitState();
	Owner->bUseControllerRotationYaw = true;

}

void UActionComponent::PressedAvoid()
{
	if (!SelectDashAction)
	{
		UE_LOG(ActionCompLog, Warning, TEXT("SelectDashAction Is NULL !!"));
		return;
	}

	Owner->SetCurrentState(EStateType::E_Avoid);

	// Init Action
	bNextAction = false;
	MontageIndex = 0;

	Owner->StopAnimMontage();
	SelectDashAction->PressedDash();
}

void UActionComponent::ReleasedAvoid()
{
	SelectDashAction->ReleasedDash();
}

void UActionComponent::DoDashMovement()
{
	if (!SelectDashAction)
	{
		UE_LOG(ActionCompLog, Warning, TEXT("SelectDashAction Is NULL !!"));
		return;
	}
	SelectDashAction->DoDashMovement();
}

void UActionComponent::OnEndDashNotify()
{
	Owner->InitState();
	Owner->bUseControllerRotationYaw = true;
	ReleasedAvoid();
}

void UActionComponent::SettingDashAction(EDashAction dash)
{
	SelectDashAction = DashActionPtr.FindRef(dash);
}

