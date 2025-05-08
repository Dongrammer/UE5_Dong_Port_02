#include "Land/Prob/DrinkingZone.h"
#include "Item/BaseItem.h"

ADrinkingZone::ADrinkingZone()
{
	ProbType = EProbType::E_RestingProb;
	RestType = ERestType::E_Drinking;
}

void ADrinkingZone::Active(ABaseHuman* human)
{
	if (human->GetUsingProb()) return;

	Super::Active(human);


	if (!bSit)
	{
		human->SetActorLocation(ActiveMeshIn->GetComponentLocation() + FVector(0, 0, 100));
		human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));

		if (DrinkingAnims.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("DrinkingZone : DrinkingAnim Array Num 0 !!"));
			return;
		}

		GetWorld()->GetTimerManager().SetTimer(DrinkingTHandle, this, &ADrinkingZone::PlayDrinkingAnims, 30.0f, true, 10.0f);
	}
	else
	{
		human->SetActorLocation(ActiveMeshIn->GetComponentLocation() + FVector(0, 0, 100));
		human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));
		human->PlayRestingAnim(ERestType::E_Seet);
		human->SetCurrentSittingType(ESittingType::E_Normal);
		GetWorld()->GetTimerManager().SetTimer(DrinkingTHandle, this, &ADrinkingZone::PlaySittingDrinkingAnims, 30.0f, true, 10.0f);
	}

	human->SetCurrentHandleType(EHandleType::E_OneHand);
	FVector location = human->GetActorLocation();
	FActorSpawnParameters param;
	if (!DrinkingCupClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrinkingZone : DrinkingCupClass Is NULL !!"));
		return;
	}
	DrinkingCup = GetWorld()->SpawnActor<ABaseItem>(DrinkingCupClass, FVector(0, 0, 0), FRotator(0, 0, 0));
	FName SocketName = "hand_l_Handle";
	if (!DrinkingCup)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrinkingZone : DrinkingCup Not Spawned !!"));
		return;
	}
	DrinkingCup->AttachToComponent(human->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

void ADrinkingZone::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);

	if (DrinkingTHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(DrinkingTHandle);
	}

	human->SetCurrentHandleType(EHandleType::E_None);
	human->SetCurrentSittingType(ESittingType::E_None);
	DrinkingCup->Destroy();
	DrinkingCup = nullptr;

}

void ADrinkingZone::PlayDrinkingAnims()
{
	if (!UsingHuman)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrinkingZone : UsingHuman Is NULL !!"));
		return;
	}

	if (DrinkingAnims.Num() == 0) return;

	int rand = FMath::RandRange(0, DrinkingAnims.Num() - 1);
	UsingHuman->PlayAnimMontage(DrinkingAnims[rand]);
}

void ADrinkingZone::PlaySittingDrinkingAnims()
{
	if (!UsingHuman)
	{
		UE_LOG(LogTemp, Warning, TEXT("DrinkingZone : UsingHuman Is NULL !!"));
		return;
	}

	if (SittingDrinkingAnims.Num() == 0) return;

	int rand = FMath::RandRange(0, DrinkingAnims.Num() - 1);
	UsingHuman->PlayAnimMontage(SittingDrinkingAnims[rand]);
}
