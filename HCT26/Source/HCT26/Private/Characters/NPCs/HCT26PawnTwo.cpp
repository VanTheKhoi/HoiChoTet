// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCs/HCT26PawnTwo.h"
#include "Core/GameLogs/GameLogsBase.h"


// Sets default values
AHCT26PawnTwo::AHCT26PawnTwo()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Firstly, create root scene component so that we can still change the box collision relative position
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	// Create, parent, and configure box collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionComponent->SetupAttachment(SceneRoot);
	CollisionComponent->SetBoxExtent(FVector(80.0f, 80.0f, 80.0f));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AHCT26PawnTwo::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind overlap events
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHCT26PawnTwo::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AHCT26PawnTwo::OnOverlapEnd);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void AHCT26PawnTwo::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		// Basic message
		GEngine->AddOnScreenDebugMessage(
			-1,                    // Key (-1 = always add new message)
			5.0f,                  // Display time in seconds
			FColor::Green,         // Text color
			TEXT("Hello My Friend !")
		);
	}
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Hello My Friend !"));

}

// ReSharper disable once CppMemberFunctionMayBeConst
void AHCT26PawnTwo::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		// Basic message
		GEngine->AddOnScreenDebugMessage(
			-1,                    // Key (-1 = always add new message)
			5.0f,                  // Display time in seconds
			FColor::Green,         // Text color
			TEXT("Bye Bye")
		);
	}
	UE_LOG(HCT26GameLogs::LogHCT, Log, TEXT("Bye Bye"));
}

// Called every frame
void AHCT26PawnTwo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHCT26PawnTwo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

