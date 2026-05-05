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
	
public:
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;
	
protected:
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY(EditAnywhere, Category="UI")
	int32 ZOrder = 0;
};
