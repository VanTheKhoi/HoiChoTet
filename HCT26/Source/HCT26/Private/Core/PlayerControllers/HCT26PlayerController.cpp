// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PlayerControllers/HCT26PlayerController.h"

#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"

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
			EnhancedInputComponent->BindAction(IA_SwitchPawn, ETriggerEvent::Triggered, this, &AHCT26PlayerController::SwitchAction);
		}
		
		// Bind the movement action
		if (IA_Movement){
			EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AHCT26PlayerController::MoveAction);
		}
	}
}

TArray<APawn*> AHCT26PlayerController::GetUnpossessedPawns()
{
	TArray<APawn*> UnpossessedPawns;
    
	// Iterate through all pawns in the world
	for (TActorIterator<APawn> It(GetWorld()); It; ++It)
	{
		APawn* IterPawn = *It;

		AController* PawnController = IterPawn->GetController();
		FString PawnName = IterPawn->GetName();
		
		// if (PawnController && PawnController->IsA<APlayerController>()) continue;
		// Only add truly unpossessed pawns
		UnpossessedPawns.Add(IterPawn);
	}
	
	return UnpossessedPawns;
}

void AHCT26PlayerController::SwitchAction(const FInputActionValue& Value)
{
	
	// Possess logic
	// Get UnPossesPawn
	TArray<APawn*> UnpossessedPawns = GetUnpossessedPawns();
	
	APawn* CurrentPawn = GetPawn();
	if (!CurrentPawn) return;
	
	// Find nearest free pawn
	float NearestDist = FLT_MAX;
	APawn* NearestPawn = nullptr;
	
	for (APawn* UnPossesPawn : UnpossessedPawns)
	{
		// Ignore if it's the current pawn
		if (UnPossesPawn == CurrentPawn) continue;
		
		// Get the nearest pawn
		float Dist = FVector::Dist(CurrentPawn->GetActorLocation(), UnPossesPawn->GetActorLocation());
		if (Dist < NearestDist)
		{
			NearestDist = Dist;
			NearestPawn = UnPossesPawn;
		}
	}
	
	if (NearestPawn)
	{
		//Possess Nearest Pawn
		Possess(NearestPawn);
	}
	
	// // Print to Screen - DEBUG
	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(
	// 		-1,                  // Key
	// 		5,     // Display Time
	// 		FColor(0, 255, 0),        // Color
	// 		TEXT("SWITCH START !!!")     // Message (FString is implicitly converted)
	// 	);
	// }
}

void AHCT26PlayerController::MoveAction(const FInputActionValue& Value)
{
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

