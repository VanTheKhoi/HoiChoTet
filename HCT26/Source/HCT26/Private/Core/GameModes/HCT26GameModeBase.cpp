// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameModes/HCT26GameModeBase.h"
#include "Core/PlayerControllers/HCT26PlayerController.h"
#include "Characters/NPCs/HCT26PawnOne.h"
#include "UI/HCT26HUD.h"

AHCT26GameModeBase::AHCT26GameModeBase()
{
	// Set custom PlayerController class
	PlayerControllerClass = AHCT26PlayerController::StaticClass();
	
	// Set custom Pawn class 
	DefaultPawnClass = AHCT26PawnOne::StaticClass();
	
	// Set custom HUD class
	HUDClass = AHCT26HUD::StaticClass();
}
