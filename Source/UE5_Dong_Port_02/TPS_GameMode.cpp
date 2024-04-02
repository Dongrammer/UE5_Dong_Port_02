#include "TPS_GameMode.h"
#include "Helper.h"

ATPS_GameMode::ATPS_GameMode()
{
	TSubclassOf<APawn> PlayerPawnClass = Helper::GetClass<APawn>(L"/Game/Characters/Hero/BP_Hero");

	if (PlayerPawnClass != NULL)
		DefaultPawnClass = PlayerPawnClass;
}
