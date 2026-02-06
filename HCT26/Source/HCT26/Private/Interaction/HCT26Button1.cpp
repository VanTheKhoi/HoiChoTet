// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HCT26Button1.h"


// Sets default values
AHCT26Button1::AHCT26Button1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCT26Button1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCT26Button1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCT26Button1::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OverlapEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OverlapEffect, GetActorLocation());
	}
}

void AHCT26Button1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

