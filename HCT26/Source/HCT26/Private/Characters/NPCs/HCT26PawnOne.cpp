// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCs/HCT26PawnOne.h"
#include "Core/GamePlayTags/HCT26GamePlayTags.h"

// Sets default values
AHCT26PawnOne::AHCT26PawnOne()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Add the "Character.CanPossess"
	TagContainer.AddTag(HCT26GameplayTags::TAG_Character_CanPossess);
}

// Called when the game starts or when spawned
void AHCT26PawnOne::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHCT26PawnOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHCT26PawnOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

