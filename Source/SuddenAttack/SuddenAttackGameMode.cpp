// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuddenAttackGameMode.h"
#include "SuddenAttackCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASuddenAttackGameMode::ASuddenAttackGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
