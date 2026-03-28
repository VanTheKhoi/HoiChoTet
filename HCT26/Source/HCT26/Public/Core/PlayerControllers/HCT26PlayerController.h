// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "HCT26PlayerController.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_SwitchPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Movement;
	
	UFUNCTION(BlueprintCallable, Category = "Pawns")
	TArray<APawn*> GetAllPawnsInScene();
	
	UFUNCTION(BlueprintCallable, Category = "Pawns")
	FString GetCurrentLevelName();
	
	UFUNCTION(BlueprintCallable, Category = "Pawns")
	bool PawnHasCanPossessTag(APawn* PawnInScene);
	
	UFUNCTION(BlueprintCallable, Category = "Pawns")
	bool PawnImplementsCanPossess(APawn* PawnInScene);
	
	void DoSwitch();
	void SwitchToNearestPawn(const FInputActionValue& Value);
	void MoveInWorld(const FInputActionValue& Value);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;
};
