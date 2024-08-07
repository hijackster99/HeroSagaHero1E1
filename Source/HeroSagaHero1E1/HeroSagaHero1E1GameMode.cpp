// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeroSagaHero1E1GameMode.h"
#include "HeroSagaHero1E1Character.h"
#include "UObject/ConstructorHelpers.h"

AHeroSagaHero1E1GameMode::AHeroSagaHero1E1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
