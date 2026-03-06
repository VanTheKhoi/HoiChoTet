// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/HCT26AirPlaneShooterEnemyBase.h"


// Sets default values
AHCT26AirPlaneShooterEnemyBase::AHCT26AirPlaneShooterEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsEnemyDead = false;
	MoveSpeed = 100.0f;
	
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
void AHCT26AirPlaneShooterEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	RandomDirection();
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &AHCT26AirPlaneShooterEnemyBase::OnHit);
}

// Called every frame
void AHCT26AirPlaneShooterEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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

// Called to bind functionality to input
void AHCT26AirPlaneShooterEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHCT26AirPlaneShooterEnemyBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GEngine)
	{
		// Basic message
		GEngine->AddOnScreenDebugMessage(
			-1,                    // Key (-1 = always add new message)
			5.0f,                  // Display time in seconds
			FColor::Green,         // Text color
			TEXT("Enemy Hit !!!")
		);
	}
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

