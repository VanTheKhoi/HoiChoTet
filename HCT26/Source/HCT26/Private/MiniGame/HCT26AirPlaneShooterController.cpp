// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniGame/HCT26AirPlaneShooterController.h"
#include "MiniGame/HCT26AirPlaneShooterPlayerBase.h"
#include "Interaction/HCT26AirPlaneShooterButton.h"

#include "Blueprint/UserWidget.h"
#include "Core/GameLogs/GameLogsBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HCT26HUD.h"


// Sets default values
AHCT26AirPlaneShooterController::AHCT26AirPlaneShooterController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsCameraShaking = false;
	
	// Create root scene component
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	// Create, parent, and configure camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SceneRoot);
	CameraComponent->SetRelativeLocation(FVector(-180.0f, 0.0f, 70.0f));
	CameraComponent->SetRelativeRotation(FRotator(-0.0f, 0.0f, 0.0f));
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);
	CameraComponent->SetFieldOfView(120.0f);
	CameraComponent->SetConstraintAspectRatio(true);
	
	// Create and parent player spawn point
	PlayerSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>("PlayerSpawnPoint");
	PlayerSpawnPoint->SetupAttachment(CameraComponent);
	PlayerSpawnPoint->SetHiddenInGame(false);

	// Create and parent enemy spawn point
	EnemySpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>("EnemySpawnPoint");
	EnemySpawnPoint->SetupAttachment(CameraComponent);
	EnemySpawnPoint->SetHiddenInGame(false);
	
}

// Called when the game starts or when spawned
void AHCT26AirPlaneShooterController::BeginPlay()
{
	Super::BeginPlay();
	
	// Print DEBUG message to LOG
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Spawn Player"));
	
	// Get the player controller
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	// Bind the StartAirPlaneShooterGame function to the StartOverlap event of the button
	Broadcaster = Cast<AHCT26AirPlaneShooterButton>(Broadcaster);
	if (Broadcaster)
	{
		Broadcaster->StartGame.AddDynamic(this, &AHCT26AirPlaneShooterController::StartAirPlaneShooterGame);
	}
	
}

// Called every frame
void AHCT26AirPlaneShooterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHCT26AirPlaneShooterController::StartAirPlaneShooterGame(bool IsStartGame)
{
	// Call SpawnPlayer function
	SpawnPlayer();
	
	// bind the dead event
	PlayerBase = Cast<AHCT26AirPlaneShooterPlayerBase>(PlayerBase);
	if (PlayerBase)
	{
		UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player Base LOAD"));
		PlayerBase->PlayerDead.AddDynamic(this, &AHCT26AirPlaneShooterController::CameraShake);
	}else
	{
		UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player Base NOTLOAD"));
	}
	
	// Call SpawnEnemy function
	SpawnEnemy();
}

void AHCT26AirPlaneShooterController::SpawnPlayer()
{
	// Check if the player controller is valid
	if (PlayerController && PlayerSPawnClass)
	{
		// Get spawn location and rotation from the PlayerSpawnPoint component
		FVector SpawnLocation = PlayerSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = PlayerSpawnPoint->GetComponentRotation();
		
		// Spawn the player pawn
		FActorSpawnParameters SpawnParams;

		// Set the spawn collision handling to always spawn, even if there are collisions
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		APawn* SpawnedPlayer = GetWorld()->SpawnActor<APawn>(
								PlayerSPawnClass,
								SpawnLocation,
								SpawnRotation,
								SpawnParams);
		
		// Check if the player was spawned successfully
		if (SpawnedPlayer)
		{
			// Possess the spawned player pawn with the player controller
			PlayerController->Possess(SpawnedPlayer);
			
			// Print DEBUG message to LOG
			UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player Spawned Successfully"));
		}
		else
		{
			// Print ERROR message to LOG
			UE_LOG(HCT26GameLogs::LogHCT, Error, TEXT("Failed to spawn player"));
		}
		
		PlayerSpawnPoint->SetHiddenInGame(true);
		
		// SetViewTargetWithBlend
		PlayerController->SetViewTargetWithBlend(this, 
												0.8f,
												VTBlend_EaseInOut,
												3.0f,
												true
												);  
		
		// Set HUD visibility to false
		AHCT26HUD* HCTHUD = Cast<AHCT26HUD>(PlayerController->GetHUD());
		if (HCTHUD)
		{
			HCTHUD->MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		// Print ERROR message to LOG
		UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("PlayerController not found"));
	}
}

void AHCT26AirPlaneShooterController::SpawnEnemy()
{
	// Get spawn location and rotation from the PlayerSpawnPoint component
	FVector SpawnLocation = EnemySpawnPoint->GetComponentLocation();
	FRotator SpawnRotation = EnemySpawnPoint->GetComponentRotation();
	
	// Spawn random location --- TO DO Random in range
	FVector RandomLocation = FVector(
		SpawnLocation.X, 
		FMath::RandRange(SpawnLocation.Y-250.0f, SpawnLocation.Y+250.0f), // Random Y between -200 and 200
		SpawnLocation.Z 
	);
	
	// Spawn the player pawn
	FActorSpawnParameters SpawnParams;

	// Set the spawn collision handling to always spawn, even if there are collisions
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
	GetWorld()->SpawnActor<APawn>(
								EnemySpawnClass,
								RandomLocation,
								SpawnRotation,
								SpawnParams
								);
	
	// Hide the enemy spawn point after spawning the enemy
	EnemySpawnPoint->SetHiddenInGame(true);
	
}

void AHCT26AirPlaneShooterController::CameraShake(bool IsPlayerDead)
{
	// Check if the player is dead and trigger camera shake
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player Dead !!!"));
	bIsCameraShaking = true;
}

