// Copyright Epic Games, Inc. All Rights Reserved.

#include "DuckDuckKazooGameMode.h"
#include "DuckDuckKazooCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADuckDuckKazooGameMode::ADuckDuckKazooGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
