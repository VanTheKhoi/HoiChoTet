// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/Interfaces/ReactToTriggerInterface.h"
#include "HCT26PawnThree.generated.h"

UCLASS()
class HCT26_API AHCT26PawnThree : public APawn, public IReactToTriggerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHCT26PawnThree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// IReactToTriggerInterface implementation
	virtual bool CanPossess() override;
};
