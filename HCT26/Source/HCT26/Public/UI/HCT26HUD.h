// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HCT26HUD.generated.h"

/**
 * 
 */

UCLASS()
class HCT26_API AHCT26HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	// // Assign the widget Blueprint (W_MainMenu) in the editor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass;
	
private:
	UPROPERTY()
	UUserWidget* MainMenuWidget;
};
