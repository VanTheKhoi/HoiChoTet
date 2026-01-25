// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "HCT26PlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHCT, Log, All); // Declare log category

/**
 * 
 */
class UInputAction;
class UInputMappingContext;

UCLASS()
class HCT26_API AHCT26PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	// Input actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_SwitchPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Movement;
	
	UFUNCTION(BlueprintCallable, Category = "Pawns")
	TArray<APawn*> GetAllPawnsInScene();
	
	UFUNCTION(BlueprintCallable, Category = "Pawns")
	FString GetCurrentLevelName();
	void DoSwitch();

	void SwitchToNearestPawn(const FInputActionValue& Value);
	void MoveInWorld(const FInputActionValue& Value);
};
