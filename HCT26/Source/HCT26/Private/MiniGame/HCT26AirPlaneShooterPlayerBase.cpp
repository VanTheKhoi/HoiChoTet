// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/HCT26AirPlaneShooterPlayerBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/GameLogs/GameLogsBase.h"
#include "Core/GamePlayTags/HCT26GamePlayTags.h"
#include "Kismet/GameplayStatics.h"
#include "MiniGame/HCT26AirPlaneShooterBulletBase.h"
#include "MiniGame/HCT26AirPlaneShooterEnemyBase.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AHCT26AirPlaneShooterPlayerBase::AHCT26AirPlaneShooterPlayerBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Setup default values
	bSpawnExplosionEffect = false;
	bIsHit = false;
	DecreasedHealth = 20.0f;
	OriginalColor = FLinearColor(0.0f, 0.2f, 1.0f, 0.1f);
	
	// Create root scene component
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	// Create, parent, and configure airplane mesh component
	AirPlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>("AirPlaneMesh");
	AirPlaneMesh->SetupAttachment(SceneRoot);
	
	// Create Cascade particle system component for explosion effect
	AirPlaneParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionEffect");
	AirPlaneParticleSystem->SetupAttachment(AirPlaneMesh);
	
	// Create, parent, and configure sphere collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionComponent->SetupAttachment(SceneRoot);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
	
	// Make sure hit events are enabled
	// CollisionComponent->SetNotifyRigidBodyCollision(true);
	
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
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHCT26AirPlaneShooterPlayerBase::OnOverlapBegin);
}

// Called every frame
void AHCT26AirPlaneShooterPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Health check - if health is 0 or below, destroy the player
	if (Health <= 0.0f && !bSpawnExplosionEffect)
	{
		if (GEngine)
		{
			// Basic message
			GEngine->AddOnScreenDebugMessage(
				-1,                    // Key (-1 = always add new message)
				5.0f,                  // Display time in seconds
				FColor::Red,           // Text color			
				TEXT("Player Destroyed !!!")
			);
		}
		
		// Spawn explosion particle effect at the player's location
		if (ExplosionParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
							ExplosionParticleSystem, 
							GetActorLocation(), 
							GetActorRotation()
							);
			
			// Hide the player mesh to simulate destruction
			AirPlaneMesh->SetVisibility(false);
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			AirPlaneParticleSystem->SetVisibility(false);
			
			// Remove all input bindings to prevent further player actions
			if (EnhancedInputComponent)
			{
				EnhancedInputComponent->ClearActionEventBindings();
			}
			
			// Broadcast player death event to notify the controller
			PlayerDead.Broadcast(true);
		}
		bSpawnExplosionEffect = true;
		// Destroy(true);
	}
	
	// Check if player was hit and apply damage
	if (bIsHit)
	{
		Damaged();
		
		// Reset hit state after applying damage
		bIsHit = false;
	}
	
	// If health is below 40, change the original color to red for the damage effect
	if (Health < 40)
	{
		OriginalColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

// Called to bind functionality to input
void AHCT26AirPlaneShooterPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (EnhancedInputComponent)
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

void AHCT26AirPlaneShooterPlayerBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if hit actor is a bullet and apply damage
	if (OtherActor && OtherActor != this)
	{
		AHCT26AirPlaneShooterBulletBase* Bullet = Cast<AHCT26AirPlaneShooterBulletBase>(OtherActor);
		AHCT26AirPlaneShooterEnemyBase* Enemy = Cast<AHCT26AirPlaneShooterEnemyBase>(OtherActor);
		
		if (Bullet)
		{
			UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player Hit Bullet"));
			
			if (Bullet->TagContainer.HasTag(HCT26GameplayTags::TAG_Bullet))
			{
				// Apply damage to the player
				DecreasedHealth = Bullet->Damage;
				bIsHit = true;
				
				// Play Hit effect
				if (HitParticleSystem)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
											HitParticleSystem, 
											Bullet->GetActorLocation());
				}
			
				// Destroy the bullet after hit
				Bullet->Destroy();
			}
		}
		
		else if (Enemy)
		{
			UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player Hit Enemy"));
			
			// Apply damage to the player
			DecreasedHealth = 100.0f;
			bIsHit = true;
		}
	}
}

void AHCT26AirPlaneShooterPlayerBase::Shoot(const FInputActionValue& Value)
{
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Shoot Action Triggered"));
	
	if (BulletClass)
	{
		// Spawn bullet at the location of the player
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		
		FVector FinalLocation = SpawnLocation + FVector(0, 0, 20);
		
		// UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Spawning Bullet at CurrentLocation: %s, FinalLocation: %s"), *SpawnLocation.ToString(), *FinalLocation.ToString());
	
		// Spawn Bullet
		FActorSpawnParameters SpawnParams;
	
		// Set the spawn collision handling to always spawn, even if there are collisions
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		GetWorld()->SpawnActor<AActor>(
								BulletClass,
								FinalLocation,
								SpawnRotation,
								SpawnParams);	
	}
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

void AHCT26AirPlaneShooterPlayerBase::CreateAndApplyDMI(FLinearColor Color, FName ParameterName)
{
	// Create a dynamic material instance for each material slot and set the specified parameter to the given color
	int32 MaterialCount = AirPlaneMesh->GetNumMaterials();
	
	for (int32 i = 0; i < MaterialCount; i++)
	{
		// Get Material 
		UMaterialInterface* Material = AirPlaneMesh->GetMaterial(i);
		
		// Check if it's a dynamic material instance
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
		
		if (!DynamicMaterial)
		{
			// If it's not a dynamic material instance, create one
			DynamicMaterial = AirPlaneMesh->CreateAndSetMaterialInstanceDynamic(i);
		}
		
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(ParameterName, Color);
		}
	}
}

void AHCT26AirPlaneShooterPlayerBase::Damaged()
{
	// Apply damage to the player
	Health -= DecreasedHealth;
			
	// Log the damage and remaining health
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Player hit by bullet! Damage: %f, Remaining Health: %f"), DecreasedHealth, Health);
			
	// Change player color to red briefly to indicate hit
	CreateAndApplyDMI(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), FName("Color1"));
			
	// Change color back to original after delay
	GetWorldTimerManager().SetTimer
	(
		DelayTimerHandle,
		[this]()
		{
			CreateAndApplyDMI( 
				OriginalColor,
				FName("Color1"));
		},
		0.3f,    // Delay in seconds
		false    // Don't loop
	);
}

