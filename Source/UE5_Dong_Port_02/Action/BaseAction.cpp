#include "Action/BaseAction.h"
#include "Character/BaseCharacter.h"

#include "Animation/AnimMontage.h"

DEFINE_LOG_CATEGORY(ActionLog);

ABaseAction::ABaseAction()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseAction::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseAction::SettingOwner(TObjectPtr<ABaseCharacter> InOwner)
{
	Owner = InOwner;
}

void ABaseAction::DoAction()
{
	UE_LOG(LogTemp, Log, TEXT("DoAction Call"));
	if (AnimAsset)
	{
		Owner->PlayAnimMontage(AnimAsset);
		UE_LOG(LogTemp, Log, TEXT("%s"), *AnimAsset.GetFName().ToString());
	}
	else
	{
		UE_LOG(ActionLog, Warning, TEXT("Action [%s] : AnimAsset Is NULL !!"), GetFName());
	}
}

