// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/HCT26AirPlaneShooterPlayerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/GameLogs/GameLogsBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHCT26AirPlaneShooterPlayerBase::AHCT26AirPlaneShooterPlayerBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create root scene component
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	// Create, parent, and configure airplane mesh component
	AirPlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>("AirPlaneMesh");
	AirPlaneMesh->SetupAttachment(SceneRoot);
	
	// Create, parent, and configure sphere collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionComponent->SetupAttachment(SceneRoot);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_Pawn);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->SetGenerateOverlapEvents(true);
	
	// Make sure hit events are enabled
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	
}

// Called when the game starts or when spawned
void AHCT26AirPlaneShooterPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Get the player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	// Log the controller class
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Current Controller: %s"), PlayerController ? *PlayerController->GetClass()->GetName() : TEXT("No Controller"));
	
	// Cast player controller 
	if (PlayerController)
	{
		// Add the input mapping context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (AirPlaneShooterPlayerMappingContext)
			{
				// Add the mapping context with higher priority
				Subsystem->AddMappingContext(AirPlaneShooterPlayerMappingContext, 1);
			}
		}
	}
	
	// Bind hit event
	CollisionComponent->OnComponentHit.AddDynamic(this, &AHCT26AirPlaneShooterPlayerBase::OnHit);
}

// Called every frame
void AHCT26AirPlaneShooterPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHCT26AirPlaneShooterPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the switch action
		if (IA_AirPlaneShooterPlayerShoot)
		{
			EnhancedInputComponent->BindAction(IA_AirPlaneShooterPlayerShoot, ETriggerEvent::Triggered, this, &AHCT26AirPlaneShooterPlayerBase::Shoot);
		}
		
		// Bind the movement action
		if (IA_AirPlaneShooterPlayerMovement){
			EnhancedInputComponent->BindAction(IA_AirPlaneShooterPlayerMovement, ETriggerEvent::Triggered, this, &AHCT26AirPlaneShooterPlayerBase::Movement);
		}
	}
}

void AHCT26AirPlaneShooterPlayerBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GEngine)
	{
		// Basic message
		GEngine->AddOnScreenDebugMessage(
			-1,                    // Key (-1 = always add new message)
			5.0f,                  // Display time in seconds
			FColor::Green,         // Text color
			TEXT("Player Hit !!!")
		);
	}
}

void AHCT26AirPlaneShooterPlayerBase::Shoot(const FInputActionValue& Value)
{
}

void AHCT26AirPlaneShooterPlayerBase::Movement(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
    
	// ========== DIRECT 2D MOVEMENT ==========
	// Log the Move Vector for debugging
	// if (GEngine)	{
	// 	GEngine->AddOnScreenDebugMessage(
	// 		0, 0.0f, FColor::Yellow,
	// 		FString::Printf(TEXT("Move Vector: X=%.2f Y=%.2f"), MoveVector.X, MoveVector.Y)
	// 	);
	// }
    
	// W/S - Up/Down on Y axis
	float UpDownMovement = MoveVector.Y * MoveSpeed;
    
	// A/D - Left/Right on X axis
	float LeftRightMovement = MoveVector.X * MoveSpeed;
    
	// Get current location
	FVector CurrentLocation = GetActorLocation();
    
	// Calculate new location (keeping X constant)
	FVector NewLocation = CurrentLocation + FVector(
		0,
		LeftRightMovement * GetWorld()->GetDeltaSeconds(),
		UpDownMovement * GetWorld()->GetDeltaSeconds()
	);
    
	// Set new location
	SetActorLocation(NewLocation);
}

