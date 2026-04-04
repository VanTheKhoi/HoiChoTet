// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HCT26AirPlaneShooterGameOverMenuBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitGameButtonClick);

UCLASS()
class HCT26_API UHCT26AirPlaneShooterGameOverMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintCallable, Category="Events")
	FOnExitGameButtonClick OnExitGameButtonClick;
};
