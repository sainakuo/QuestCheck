// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestCheckGameMode.h"
#include "QuestCheckCharacter.h"
#include "UObject/ConstructorHelpers.h"

AQuestCheckGameMode::AQuestCheckGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
