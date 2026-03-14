// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/HCT26AirPlaneShooterEnemyBase.h"
#include "MiniGame/HCT26AirPlaneShooterBulletBase.h"

#include "Core/GameLogs/GameLogsBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHCT26AirPlaneShooterEnemyBase::AHCT26AirPlaneShooterEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsEnemyDead = false;
	bIsStopMovement = false;
	bIsSuicide = false;
	MoveSpeed = 100.0f;
	OriginalColor = FLinearColor(1.0f, 0.3f, 0.0f, 0.1f);
	
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
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
	
}

// Called when the game starts or when spawned
void AHCT26AirPlaneShooterEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	RandomDirection();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHCT26AirPlaneShooterEnemyBase::OnOverlapBegin);

	
}

// Called every frame
void AHCT26AirPlaneShooterEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move the enemy left and right
	MoveLeftRight(DeltaTime);
	
	// Check if enemy is on suicide mode
	EnemySuicide(DeltaTime);
	
	// Check if enemy is dead and handle death logic
	EnemyDeath();
}

// Called to bind functionality to input
void AHCT26AirPlaneShooterEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHCT26AirPlaneShooterEnemyBase::RandomDirection()
{
	// Randomly choose left or right
	int32 RandomChoice = FMath::RandRange(0, 1);
	if (RandomChoice == 0)
	{
		CurrentVelocity = FVector(0.0f, MoveSpeed, 0.0f); // right
	}
	else
	{
		CurrentVelocity = FVector(0.0f, -MoveSpeed, 0.0f); // left
	}
}

void AHCT26AirPlaneShooterEnemyBase::MoveLeftRight(float DeltaTime)
{
	if (!bIsSuicide)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += CurrentVelocity * DeltaTime;
	
		SetActorLocation(CurrentLocation);
	
		// Boundary check
		if (CurrentLocation.Y < 1390.0f)
		{
			CurrentVelocity = FVector(0.0f, MoveSpeed, 0.0f); // move right
		}
	
		else if (CurrentLocation.Y > 1790.0f)
		{
			CurrentVelocity = FVector(0.0f, -MoveSpeed, 0.0f); // move left
		}
	}
}

void AHCT26AirPlaneShooterEnemyBase::EnemyDeath()
{
	if (bIsEnemyDead && !bSpawnExplosionEffect)
	{
		// Play explosion effect, disable mesh and collision, and set enemy as dead
		if (ExplosionParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
									ExplosionParticleSystem, 
									GetActorLocation());
		}
		
		bSpawnExplosionEffect = true;
		
		// Destroy
		Destroy(true);
	}
	
	// Check if enemy is out of bounds (below Z = 93) and handle death logic
	else if (GetActorLocation().Z < 93.0f && !bSpawnExplosionEffect)
	{
		// Play explosion effect, disable mesh and collision, and set enemy as dead
		if (ExplosionParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), 
									ExplosionParticleSystem, 
									GetActorLocation());
		}
		
		bSpawnExplosionEffect = true;
		
		// Destroy
		Destroy(true);
	}
}

void AHCT26AirPlaneShooterEnemyBase::EnemySuicide(float DeltaTime)
{
	if (bIsSuicide)
	{
		if (!bIsStopMovement)
		{
			MoveSpeed = 0.0f;
			bIsStopMovement = true;
			
			// Delay the change of MoveSpeed to create a pause before moving downwards
			GetWorldTimerManager().SetTimer
			(
				DelayTimerHandle,
				[this]()
				{
					MoveSpeed = 350.0f;
				},
				0.5f,    // Delay in seconds
				false    // Don't loop
			);
		}
		
		CurrentVelocity = FVector(0.0f, 0.0f, -MoveSpeed); // Move downwards
		
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += CurrentVelocity * DeltaTime;
	
		SetActorLocation(CurrentLocation);
	}
}

void AHCT26AirPlaneShooterEnemyBase::CreateAndApplyDMI(FLinearColor Color, FName ParameterName)
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

void AHCT26AirPlaneShooterEnemyBase::Damaged()
{
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

void AHCT26AirPlaneShooterEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AHCT26AirPlaneShooterBulletBase* Bullet = Cast<AHCT26AirPlaneShooterBulletBase>(OtherActor);
		
		if (Bullet)
		{
			// Apply damage to enemy
			Health -= Bullet->Damage;
			
			// // Log the damage and remaining health
			// if (GEngine)
			// {
			// 	// Basic message
			// 	GEngine->AddOnScreenDebugMessage(
			// 		-1,                    // Key (-1 = always add new message)
			// 		5.0f,                  // Display time in seconds
			// 		FColor::Green,         // Text color
			// 		TEXT("Health: ") + FString::SanitizeFloat(Health)
			// 	);
			// }
			
			Damaged();
			
			// Check if enemy is dead
			if (Health <= 0.0f)
			{
				bIsEnemyDead = true;
			}
			
			else if (Health <= 40.0f)
			{
				bIsSuicide = true;
				OriginalColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
			}
			
			// Destroy the bullet
			Bullet->Destroy(true);
		}

	}
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Enemy Hit"));
}

