// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HCT26Button2.h"


// Sets default values
AHCT26Button2::AHCT26Button2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCT26Button2::BeginPlay()
{
	Super::BeginPlay();
	StartOverlap.AddDynamic(this, &AHCT26Button2::ExecuteFXOverlap);
}

// Called every frame
void AHCT26Button2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCT26Button2::ExecuteFXOverlap(AActor* OverlappingActor)
{
	if (OverlapEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OverlapEffect, GetActorLocation());
	}
}

