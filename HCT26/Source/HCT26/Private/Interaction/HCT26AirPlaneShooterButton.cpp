// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HCT26AirPlaneShooterButton.h"
#include "Core/GameLogs/GameLogsBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHCT26AirPlaneShooterButton::AHCT26AirPlaneShooterButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCT26AirPlaneShooterButton::BeginPlay()
{
	Super::BeginPlay();
	StartOverlap.AddDynamic(this, &AHCT26AirPlaneShooterButton::StartAirPlaneShooterGame);
}

// Called every frame
void AHCT26AirPlaneShooterButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCT26AirPlaneShooterButton::StartAirPlaneShooterGame(AActor* OverlappingActor)
{
	// Debug message
	// UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Start AirPlaneShooter Game!"));
	
	// Broadcast the StartGame event with true to indicate the game should start
	StartGame.Broadcast(true);
}

