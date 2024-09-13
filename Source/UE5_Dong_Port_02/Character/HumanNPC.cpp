#include "Character/HumanNPC.h"

#include "Helper.h"

DEFINE_LOG_CATEGORY(HumanNPCLog);

AHumanNPC::AHumanNPC()
{
	CreateCharacter();
}

void AHumanNPC::BeginPlay()
{
	Super::BeginPlay();

	//SortRoutines();
}

void AHumanNPC::CreateCharacter()
{
	Super::CreateCharacter();

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>(L"/Game/Characters/HumanNPC/ABP_HumanNPC"));
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
