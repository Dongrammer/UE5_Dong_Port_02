// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_Dong_Port_02GameMode.h"
#include "UE5_Dong_Port_02Character.h"
#include "UObject/ConstructorHelpers.h"

AUE5_Dong_Port_02GameMode::AUE5_Dong_Port_02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
