// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/HCT26AirPlaneShooterBulletBase.h"
#include "Core/GamePlayTags/HCT26GamePlayTags.h"
#include "TimerManager.h"


// Sets default values
AHCT26AirPlaneShooterBulletBase::AHCT26AirPlaneShooterBulletBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create root scene component
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	// Create, parent, and configure airplane mesh component
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	BulletMesh->SetupAttachment(SceneRoot);
	
	// Create, parent, and configure sphere collision component
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionComponent->SetupAttachment(SceneRoot);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_Pawn);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->SetGenerateOverlapEvents(true);
	
	// Make sure hit events are enabled
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	
	// Create and configure projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = BulletSpeed;
	ProjectileMovementComponent->MaxSpeed = BulletSpeed;
	ProjectileMovementComponent->Velocity = FVector(0, 0, BulletSpeed);
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	// Add Tag
	TagContainer.AddTag(HCT26GameplayTags::TAG_Bullet);
	
}

// Called when the game starts or when spawned
void AHCT26AirPlaneShooterBulletBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Set a timer to destroy the bullet after DestroyTime seconds
	GetWorldTimerManager().SetTimer(
		DestroyTimerHandle,
		[this]()
		{
			Destroy(true);
		},
		DestroyTime,
		false
	);
}

// Called every frame
void AHCT26AirPlaneShooterBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCT26AirPlaneShooterBulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

