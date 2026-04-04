// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Players/HCT26MainPlayerBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AHCT26MainPlayerBase::AHCT26MainPlayerBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Enable rotation to follow the controller
	bUseControllerRotationYaw = true;
	
	// Create collision component as root
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
	
	// // Spring arm setup
	// CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// CameraBoom->SetupAttachment(CollisionComponent);
	// CameraBoom->TargetArmLength = 300.0f;
	// CameraBoom->bUsePawnControlRotation = true;
	//
	// // Camera setup
	// PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	// PawnCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// PawnCamera->bUsePawnControlRotation = false;
	
	// FloatingPawnMovement automatically handles ConsumeMovementInputVector
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void AHCT26MainPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCT26MainPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHCT26MainPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// void AHCT26MainPlayerBase::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
// {
// 	Super::CalcCamera(DeltaTime, OutResult);
//
// 	if (PawnCamera)
// 	{
// 		PawnCamera->GetCameraView(DeltaTime, OutResult);
// 	}
// }

