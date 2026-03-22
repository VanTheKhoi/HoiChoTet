// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HCT26AirPlaneShooterGameMenuBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayGameButtonClicked);

UCLASS()
class HCT26_API UHCT26AirPlaneShooterGameMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Mark as BlueprintAssignable so designers can hook it up in Blueprints
	UPROPERTY(BlueprintCallable, Category="Events")
	FOnPlayGameButtonClicked PlayGame;
};
