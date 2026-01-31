// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Players/HCT26MainPlayerBase.h"


// Sets default values
AHCT26MainPlayerBase::AHCT26MainPlayerBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCT26MainPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCT26MainPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHCT26MainPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

