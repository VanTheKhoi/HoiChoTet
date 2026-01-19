// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HCT26HUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AHCT26HUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (WidgetClass)
	{
		// Create the widget instance
		MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	
		if (MainMenuWidget)
		{
			// Add to viewport
			MainMenuWidget->AddToViewport();
		}
	}
	
	// Show mouse cursor and enable UI interaction
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(InputMode);
	}
}