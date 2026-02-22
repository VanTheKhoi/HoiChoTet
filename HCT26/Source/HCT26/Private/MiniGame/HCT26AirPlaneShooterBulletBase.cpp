// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/HCT26AirPlaneShooterBulletBase.h"


// Sets default values
AHCT26AirPlaneShooterBulletBase::AHCT26AirPlaneShooterBulletBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCT26AirPlaneShooterBulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCT26AirPlaneShooterBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

