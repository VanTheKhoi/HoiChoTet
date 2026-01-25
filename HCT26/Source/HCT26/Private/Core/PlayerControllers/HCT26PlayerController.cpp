// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerControllers/HCT26PlayerController.h"

#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogHCT); // Define log category

void AHCT26PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			// Add the mapping context with priority 0 (default)
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AHCT26PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the switch action
		if (IA_SwitchPawn)
		{
			EnhancedInputComponent->BindAction(IA_SwitchPawn, ETriggerEvent::Triggered, this, &AHCT26PlayerController::SwitchToNearestPawn);
		}
		
		// Bind the movement action
		if (IA_Movement){
			EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AHCT26PlayerController::MoveInWorld);
		}
	}
}

TArray<APawn*> AHCT26PlayerController::GetAllPawnsInScene()
{
	TArray<APawn*> AllPawnsInWorld;
    
	// Iterate through all pawns in the world
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		APawn* IterPawn = *It;
		AllPawnsInWorld.Add(IterPawn);
	}
	
	UE_LOG(LogHCT, Log, TEXT("Total Pawns in World: %d"), AllPawnsInWorld.Num());
	return AllPawnsInWorld;
}

FString AHCT26PlayerController::GetCurrentLevelName()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true); 
	return CurrentLevelName;
}

void AHCT26PlayerController::DoSwitch()
{
	// Possess logic
	TArray<APawn*> AllPawns = GetAllPawnsInScene();

	APawn* CurrentPawn = GetPawn();
	FVector SearchLocation = FVector::ZeroVector;

	if (CurrentPawn)
	{
		SearchLocation = CurrentPawn->GetActorLocation();
	}
	else
	{
		// Try to find a PlayerStart if no pawn is possessed
		AActor* FoundPlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
		if (FoundPlayerStart)
		{
			SearchLocation = FoundPlayerStart->GetActorLocation();
			UE_LOG(LogHCT, Log, TEXT("Found PlayerStart at location: %s"), *SearchLocation.ToString());
		}
		// Else it remains FVector::ZeroVector (World Origin)
	}
	
	// Find nearest free pawn
	float NearestDist = FLT_MAX;
	APawn* NearestPawn = nullptr;
	
	for (APawn* PawnInScene : AllPawns)
	{
		// Ignore if it's the current pawn
		if (CurrentPawn && PawnInScene == CurrentPawn) continue;
		
		// Get the nearest pawn
		float Dist = FVector::Dist(SearchLocation, PawnInScene->GetActorLocation());
		if (Dist < NearestDist)
		{
			NearestDist = Dist;
			NearestPawn = PawnInScene;
		}
	}
	
	UE_LOG(LogHCT, Log, TEXT("Nearest Pawn: %s at distance: %f"), NearestPawn ? *NearestPawn->GetName() : TEXT("None"), NearestDist);
	
	if (NearestPawn)
	{
		//Possess Nearest Pawn
		Possess(NearestPawn);
	}
	
}

void AHCT26PlayerController::SwitchToNearestPawn(const FInputActionValue& Value)
{
	DoSwitch();
}

void AHCT26PlayerController::MoveInWorld(const FInputActionValue& Value)
{
	// FString CurrentLevelName = GetCurrentLevelName();
	// UE_LOG(LogHCT, Log, TEXT("Current level: %s"), *CurrentLevelName);
	// if (CurrentLevelName == "WelcomeLevel") return;
	
	// Implement move logic here
	FVector2D MovementVector = Value.Get<FVector2D>();
	APawn* ControlledPawn = GetPawn(); // Get Default Pawn
	
	if (ControlledPawn)
	{
		// UE_LOG(LogTemp, Log, TEXT("Move Action Triggered NEW NEW"));
		const FRotator Rotation = ControlledPawn->GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		// Get forward and right vectors
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
