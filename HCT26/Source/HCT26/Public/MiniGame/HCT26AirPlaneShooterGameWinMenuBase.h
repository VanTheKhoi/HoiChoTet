// Fill out your copyright notice in the Description page o
// f Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HCT26AirPlaneShooterGameWinMenuBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitGameWinButtonClick);

UCLASS()
class HCT26_API UHCT26AirPlaneShooterGameWinMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintCallable, Category="Events")
	FOnExitGameWinButtonClick OnExitGameWinButtonClick;
};
