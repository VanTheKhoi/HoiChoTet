// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyGameFeatureAction.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

void UMyGameFeatureAction::OnGameFeatureActivating(FGameFeatureActivatingContext& Context)
{
	Super::OnGameFeatureActivating(Context);
	UE_LOG(LogTemp, Log, TEXT("Activating MyGameFeatureAction"));

	if (!WidgetClass) return;

	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		UWorld* World = WorldContext.World();
		if (!World) continue;

		UUserWidget* Widget = CreateWidget<UUserWidget>(World, WidgetClass);
		if (Widget)
		{
			Widget->AddToViewport(ZOrder);
		}
	}
}

void UMyGameFeatureAction::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	Super::OnGameFeatureDeactivating(Context);
}
