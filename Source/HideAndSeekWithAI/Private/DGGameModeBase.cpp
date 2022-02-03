// Fill out your copyright notice in the Description page of Project Settings.


#include "DGGameModeBase.h"

#include "DGCharacter.h"
#include "DGHUD.h"
#include "DGPlayerController.h"

ADGGameModeBase::ADGGameModeBase()
{
	DefaultPawnClass = ADGCharacter::StaticClass();
	PlayerControllerClass = ADGPlayerController::StaticClass();
	HUDClass = ADGHUD::StaticClass();
}
