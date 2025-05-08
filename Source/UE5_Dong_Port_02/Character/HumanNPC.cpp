#include "Character/HumanNPC.h"


#include "../Land/Prob/BaseProb.h"
#include "Land/Prob/Anvil.h"
#include "Land/Prob/GuardPoint.h"
#include "Land/Prob/Shop.h"
#include "Components/WidgetComponent.h"
#include "Character/Hero.h"
//#include "Helper.h"

DEFINE_LOG_CATEGORY(HumanNPCLog);

AHumanNPC::AHumanNPC()
{
	CreateCharacter();

	PushedCapsule = Helper::CreateSceneComponent<UCapsuleComponent>(this, "Pushed Capsule", BodyCollision);
	PushedCapsule->InitCapsuleSize(50.0f, 100.0f);
	PushedCapsule->SetCollisionProfileName("Custom");
	PushedCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PushedCapsule->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	PushedCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PushedCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//HealthBar = CreateWidget<UNPCHealthBar>(this, HealthBarClass, TEXT("Health Bar"));
	//HealthBar = Cast<UNPCHealthBar>(CreateWidget(GetWorld(), HealthBarClass, TEXT("Health Bar")));

}

void AHumanNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Pushed
	if (OverlapHuman.Num() > 0)
	{
		if (CheckBehavior(EBehaviorType::E_Working)) return;

		FVector dir = GetActorLocation() - OverlapHuman[0]->GetActorLocation();
		dir.Normalize();

		// Set Direction
		float ForwardDot = FVector::DotProduct(dir, GetActorForwardVector());
		float RightDot = FVector::DotProduct(dir, GetActorRightVector());

		EPushedDirection hitdir = EPushedDirection::E_Forward;
		if (ForwardDot <= -0.7f)
		{
			hitdir = EPushedDirection::E_Forward;
		}
		else if (ForwardDot > 0.7f)
		{
			hitdir = EPushedDirection::E_Back;
		}
		else if (RightDot <= -0.7f)
		{
			hitdir = EPushedDirection::E_Right;
		}
		else if (RightDot > 0.7f)
		{
			hitdir = EPushedDirection::E_Left;
		}

		float speed = OverlapHuman[0]->GetCurrentSpeed();

		if (bCanMove)
		{
			if (speed <= 200)
			{
				AddActorWorldOffset(dir * 0.1f, true);
			}
			else if (speed <= 400)
			{
				PlayPushedAnim(hitdir, EPushType::E_Push);
				LaunchCharacter(dir * 800.0f, true, true);
				Decreasedlikeability(5);
			}
			else
			{
				PlayPushedAnim(hitdir, EPushType::E_StrongPush);
				LaunchCharacter(dir * 1200.0f, true, true);
				Decreasedlikeability(5);
			}
		}
	}
}

void AHumanNPC::BeginPlay()
{
	Super::BeginPlay();

	PushedCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHumanNPC::OnBeginOverlap);
	PushedCapsule->OnComponentEndOverlap.AddDynamic(this, &AHumanNPC::OnEndOverlap);
	SortRoutines();

	/* ========== Set WorkProb ========== */
	if (!AffiliatedVillage)
	{
		UE_LOG(HumanNPCLog, Warning, TEXT("AffiliatedVillage Is NULL !!"));
		return;
	}
	SetWorkProb();

	/* ========== Set Village ========== */
	AffiliatedVillage->AddVillageNPC(this);
}

void AHumanNPC::CreateCharacter()
{
	Super::CreateCharacter();

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>(L"/Game/Characters/HumanNPC/ABP_HumanNPC"));
}

void AHumanNPC::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(OtherComp->GetOwner());

	if (!human || human == this) return;

	OverlapHuman.AddUnique(human);
}

void AHumanNPC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(OtherComp->GetOwner());

	if (!human || human == this) return;

	if (OverlapHuman.Contains(human))
		OverlapHuman.Remove(human);
}

void AHumanNPC::OneMinuteTimePass()
{
	Super::OneMinuteTimePass();
}

FVector AHumanNPC::GetHomeLocation()
{
	if (!Home)
	{
		UE_LOG(HumanNPCLog, Warning, TEXT("Home Is NULL !!"));
		return FVector::Zero();
	}

	return Home->GetActorLocation();
}

void AHumanNPC::SortRoutines()
{
	TArray<TPair<ERoutineType, FGlobalTime>> rou;
	rou.Append(Routines.Array());

	rou.Sort([](const TPair<ERoutineType, FGlobalTime>& A, const TPair<ERoutineType, FGlobalTime>& B)
		{
			return A.Value.CurrentTime > B.Value.CurrentTime; // 내림차순 정렬
		});

	Routines.Empty();

	for (const TPair<ERoutineType, FGlobalTime>& r : rou)
	{
		Routines.Add(r);
	}
}

void AHumanNPC::SetWorkProb()
{
	for (auto job : Jobs)
	{
		switch (job)
		{
		case EJobType::E_Blacksmith:
		{
			TArray<TObjectPtr<AAnvil>> anvils = AffiliatedVillage->GetProbs<AAnvil>();
			TObjectPtr<AAnvil> tempanvil;
			if (anvils.Num() > 0)
			{
				tempanvil = anvils[0];
				for (int i = 1; i < anvils.Num(); i++)
				{
					if (GetDistanceTo(tempanvil) > GetDistanceTo(anvils[i]))
					{
						tempanvil = anvils[i];
					}
				}
			}

			WorkProbs.Add(tempanvil);
			break;
		}
		case EJobType::E_Guard:
		{
			TArray<TObjectPtr<AGuardPoint>> points = AffiliatedVillage->GetProbs<AGuardPoint>();

			if (points.Num() > 0)
			{
				for (TObjectPtr<AGuardPoint> p : points)
				{
					WorkProbs.Add(p);
				}
			}
			break;
		}
		case EJobType::E_ShopKeeper:
		{
			TArray<TObjectPtr<AShop>> shops = AffiliatedVillage->GetProbs<AShop>();
			for (auto shop : shops)
			{
				if (shop)
				{
					UE_LOG(LogTemp, Log, TEXT("%s"), *shop.GetFName().ToString());
					WorkProbs.Add(shop);
				}
			}
			/*TObjectPtr<AShop> shop = Cast<AShop>(Home->GetInsideProbs<AShop>()[0]);
			if (shop)
			{

				WorkProbs.Add(shop);
			}
			break;*/
		}
		}
	}
}

void AHumanNPC::StartWork(EWorkType type)
{
	switch (type)
	{
	case EWorkType::E_UseAnvil:
	{
		FatigueValue = 150;
		break;
	}
	case EWorkType::E_Guard:
	{
		FatigueValue = 100;
		break;
	}
	}
	GetWorld()->GetTimerManager().SetTimer(ConditionTimerHandle, this, &AHumanNPC::UpdateCondition, 1.0f, true);
}

void AHumanNPC::StopWork()
{
	GetWorld()->GetTimerManager().ClearTimer(ConditionTimerHandle);
}

void AHumanNPC::SetRandomHobby()
{
	if (Hobbies.Num() == 0) return;
	else if (Hobbies.Num() == 1)
	{
		TArray<TPair<EHobbies, uint8>> hobbies = Hobbies.Array();
		CurrentHobby = hobbies[0].Key;
	}
	else
	{
		// If don't set the probability
		bool s = false;
		for (auto hobby : Hobbies)
		{
			if (hobby.Value == 0)
				s = true;
		}
		if (s)
		{
			for (auto& hobby : Hobbies)
				hobby.Value = 1;
		}

		// Hobbies GCD
		TArray<TPair<EHobbies, uint8>> hobbies = Hobbies.Array();

		for (int i = 1; i < hobbies.Num(); i++)
		{
			while (hobbies[i - 1].Value != 0)
			{
				int temp = hobbies[i].Value % hobbies[i - 1].Value;
				hobbies[i].Value = hobbies[i - 1].Value;
				hobbies[i - 1].Value = temp;
			}
		}

		uint8 r = hobbies[hobbies.Num() - 1].Value;
		//UE_LOG(HumanNPCLog, Log, TEXT("%s : Hobbies GCD : %d"), *this->GetFName().ToString(), r);
		
		// Set Array
		TArray<EHobbies> HobbyArray;
		uint8 TotalProbability = 0;
		hobbies = Hobbies.Array();
		for (int i = 0; i < hobbies.Num(); i++)
		{
			TotalProbability += hobbies[i].Value / r;
			for (int j = 0; j < hobbies[i].Value / r; j++)
			{
				HobbyArray.Add(hobbies[i].Key);
			}
		}

		// Set Random Hobby
		uint8 rand = FMath::RandRange(0, TotalProbability - 1);

		CurrentHobby = HobbyArray[rand];
	}
	//UE_LOG(HumanNPCLog, Log, TEXT("%s : Current Hobby : %d"), *this->GetFName().ToString(), static_cast<uint8>(CurrentHobby));
}

void AHumanNPC::InitCondition()
{
	CurrentFatigue = 0;
}

void AHumanNPC::UpdateCondition()
{
	int Rand = FMath::RandRange(-(FatigueValue / 10), (FatigueValue / 10));
	CurrentFatigue += (FatigueValue + Rand) * (1.0f - (Endurance * 0.01));

	if (CurrentFatigue > MaxFatigue)
		CurrentFatigue = MaxFatigue;
}

void AHumanNPC::RecoveryFatigue(uint8 percent)
{
	int val = MaxFatigue * ((float)percent * 0.01f);
	if ((CurrentFatigue - val) < 0)
	{
		CurrentFatigue = 0;
	}
	else
	{
		CurrentFatigue -= val;
	}

}

void AHumanNPC::EndActionNotify()
{
	InitState();
}

void AHumanNPC::Increasedlikeability(int n)
{
	Likeability += n;
}

void AHumanNPC::Decreasedlikeability(int n)
{
	Likeability -= n;
}

void AHumanNPC::TakeDamageFuc(AActor* damagecauser, int damage, FVector hittedlocation)
{
	Super::TakeDamageFuc(damagecauser, damage, hittedlocation);

	// Player Likeability
	Decreasedlikeability(30);

	TObjectPtr<AHero> player = Cast<AHero>(damagecauser);
	if (!player)
	{
		UE_LOG(HumanNPCLog, Warning, TEXT("TakeDamageFuc : damagecauser casting to hero fail"));
		return;
	}

	if (AffiliatedVillage)
	{
		TArray<TObjectPtr<AHumanNPC>> npcs = AffiliatedVillage->GetAllVillageNPCs();

		for (auto npc : npcs)
		{
			npc->Decreasedlikeability(10);
		}
	}
}

//void AHumanNPC::SortRoutines()
//{
//	TArray<ERoutineType> keys;
//	TArray<FGlobalTime> Values;
//
//	for (int i = 0; i < static_cast<uint8>(ERoutineType::E_Max); i++)
//	{
//		ERoutineType RT = static_cast<ERoutineType>(i);
//		if (Routines.Contains(RT))
//		{
//			keys.Add(RT);
//			Values.Add(Routines.FindRef(RT));
//		}
//	}
//
//	if (keys.Num() >= 2)
//	{
//		bool k = true;
//		while (k)
//		{
//			k = false;
//			for (int i = 0; i < Values.Num() - 1; i++)
//			{
//				if (Values[i].CurrentHour > Values[i + 1].CurrentHour)
//				{
//					Values.Swap(i, i + 1);
//					keys.Swap(i, i + 1);
//					k = true;
//				}
//				else if (Values[i].CurrentHour == Values[i + 1].CurrentHour)
//				{
//					if (Values[i].CurrentMinute > Values[i + 1].CurrentMinute)
//					{
//						Values.Swap(i, i + 1);
//						keys.Swap(i, i + 1);
//						k = true;
//					}
//				}
//			}
//		}
//	}
//
//	Routines.Empty();
//
//	for (int i = 0; i < keys.Num(); i++)
//	{
//		Routines.Add(keys[i], Values[i]);
//	}
//
//
//}
