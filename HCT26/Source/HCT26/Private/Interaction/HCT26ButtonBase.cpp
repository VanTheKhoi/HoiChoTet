// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HCT26ButtonBase.h"


// Sets default values
AHCT26ButtonBase::AHCT26ButtonBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create root scene component
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	// Create, parent, and configure box collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AHCT26ButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind overlap events
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHCT26ButtonBase::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AHCT26ButtonBase::OnOverlapEnd);
}

// Called every frame
void AHCT26ButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHCT26ButtonBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	StartOverlap.Broadcast(OtherActor);
}

void AHCT26ButtonBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	EndOverlap.Broadcast(OtherActor);
}

