#include "TPS_GameInstance.h"

void UTPS_GameInstance::Init()
{
	Super::Init();

	ItemComponentInstance = NewObject<UItemComponent>(this);
	ItemComponentInstance->SetRarityColor();
	
}

void UTPS_GameInstance::OnStart()
{
	Super::OnStart();

	InitGlobalTime();
}

UItemComponent* UTPS_GameInstance::GetItemComponent()
{
	return ItemComponentInstance;
}

void UTPS_GameInstance::InitGlobalTime()
{
	TimerManager->SetTimer(SetGlobalTime, this, &UTPS_GameInstance::OneMinuteTimePass, 1 / TimeMult, true);
	GlobalTime.CurrentWeek = EWeekType::E_Monday;
	GlobalTime.CurrentHour = 9;
}

void UTPS_GameInstance::OneMinuteTimePass()
{
	GlobalTime.CurrentMinute++;
	if (GlobalTime.CurrentMinute >= 60)
	{
		GlobalTime.CurrentMinute = 0;
		GlobalTime.CurrentHour++;
	}
	if (GlobalTime.CurrentHour >= 24)
	{
		GlobalTime.CurrentHour = 0;
		GlobalTime.CurrentDay++;

		// Set Week
		uint8 tempWeek = static_cast<uint8>(GlobalTime.CurrentWeek);
		if (tempWeek >= static_cast<uint8>(EWeekType::E_SunDay))
			tempWeek = 0;
		tempWeek++;
		GlobalTime.CurrentWeek = static_cast<EWeekType>(tempWeek);
	}
	/*CurrentMinute++;
	if (CurrentMinute >= 60)
	{
		CurrentMinute = 0;
		CurrentHour++;
	}

	if (CurrentHour >= 24)
	{
		CurrentHour = 0;
		CurrentDay++;
	}*/

	if (DOneMinuteTimePass.IsBound())
		DOneMinuteTimePass.Broadcast();
}
void UTPS_GameInstance::SetTimeMult(float f)
{
	TimeMult = f;
	TimerManager->ClearTimer(SetGlobalTime);
	TimerManager->SetTimer(SetGlobalTime, this, &UTPS_GameInstance::OneMinuteTimePass, 1 / TimeMult, true);

}
//
//TArray<uint8> UTPS_GameInstance::GetGlobalTime()
//{
//	TArray<uint8> times;
//	times.Add(CurrentDay);
//	times.Add(CurrentHour);
//	times.Add(CurrentMinute);
//
//	return times;
//}
