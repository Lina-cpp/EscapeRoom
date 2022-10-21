// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeRoomGameMode.h"
#include "EscapeRoomCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEscapeRoomGameMode::AEscapeRoomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MyStuff/Character/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
