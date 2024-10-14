// Copyright Epic Games, Inc. All Rights Reserved.

#include "GasRPGDemo1GameMode.h"
#include "GasRPGDemo1Character.h"
#include "UObject/ConstructorHelpers.h"

AGasRPGDemo1GameMode::AGasRPGDemo1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
