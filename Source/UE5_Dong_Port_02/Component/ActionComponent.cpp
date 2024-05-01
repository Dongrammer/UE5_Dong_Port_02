#include "Component/ActionComponent.h"

#include "Action/ActionDataAsset.h"
#include "Action/BaseAction.h"

#include "../Character/Hero.h"
#include "../Character/BaseCharacter.h"
#include "Helper.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ActionDataAsset = Helper::GetAsset<UActionDataAsset>(L"/Game/Actions/DA_Action");
}

void UActionComponent::SetOwner(AHero* hero)
{
	Owner = hero;
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CreateActions();

	//SelectActions.Add(GauntletActionPtr.FindRef(EGauntletAction::E_LeftJap_01));
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActionComponent::SettingActions(TArray<TSubclassOf<ABaseAction>> actions)
{
	for (int i = 0; i < actions.Num(); i++)
	{
		if (!actions[i]) break;


	}
}

void UActionComponent::CreateActions()
{
	for (auto& AcData : ActionDataAsset->Gauntlet_Actions)
	{
		TObjectPtr<ABaseAction> action = GetWorld()->SpawnActor<ABaseAction>(AcData.Value);
		GauntletActionPtr.Add(AcData.Key, action);
		action->SettingOwner(Cast<ABaseCharacter>(GetOwner()));
	}

	for (auto& AcData : ActionDataAsset->Sword_Actions)
	{
		TObjectPtr<ABaseAction> action = NewObject<ABaseAction>(this, AcData.Value);
		SwordActionPtr.Add(AcData.Key, action);
		action->SettingOwner(Cast<ABaseCharacter>(GetOwner()));
	}
}

void UActionComponent::DoAction()
{
	uint8 index = 0;

	if (SelectActions.IsEmpty() || !SelectActions[index]) return;

	SelectActions[index]->DoAction();
}

void UActionComponent::EndAction()
{
}

