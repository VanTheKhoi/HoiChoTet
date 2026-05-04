// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "MyGameFeatureAction.generated.h"

/**
 * 
 */
UCLASS()
class HCT26_API UMyGameFeatureAction : public UGameFeatureAction
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(EditAnywhere, Category="UI")
	int32 ZOrder = 0;
	
};
