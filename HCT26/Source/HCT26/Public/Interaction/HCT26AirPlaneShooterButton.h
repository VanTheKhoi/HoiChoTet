// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HCT26ButtonBase.h"
#include "HCT26AirPlaneShooterButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignatureStartGame, bool, IsStartGame);

UCLASS()
class HCT26_API AHCT26AirPlaneShooterButton : public AHCT26ButtonBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCT26AirPlaneShooterButton();
	
	UPROPERTY(BlueprintAssignable, Category=HoiChoTet)
	FSignatureStartGame StartGame;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Start Game
	UFUNCTION()
	void StartAirPlaneShooterGame(AActor* OverlappingActor);
};
