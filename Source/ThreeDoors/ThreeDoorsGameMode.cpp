// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThreeDoorsGameMode.h"
#include "ThreeDoorsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThreeDoorsGameMode::AThreeDoorsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
