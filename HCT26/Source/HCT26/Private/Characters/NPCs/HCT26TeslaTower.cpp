// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCs/HCT26TeslaTower.h"


// Sets default values
AHCT26TeslaTower::AHCT26TeslaTower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create root scene component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	//Create mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseTeslaTowerMesh");
	MeshComp->SetupAttachment(SceneRoot);
	
	// Create a Niagara component for shooting effect and attach to root
	ShootEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Shoot Effect Niagara Component"));
	ShootEffect->SetupAttachment(SceneRoot);
	
	// Create a Niagara component for area effect and attach to root
	AreaEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Area Effect Niagara Component"));
	AreaEffect->SetupAttachment(SceneRoot);
	
	// Initialize cached pawn pointer
	CachedPlayerPawn = nullptr;
}

void AHCT26TeslaTower::UpdateAreaEffectParameters(float Radius, float Height, FLinearColor Color)
{
	if (AreaEffect != nullptr)
	{
		AreaEffect->SetFloatParameter(FName("Radius"), Radius);
		AreaEffect->SetFloatParameter(FName("Height"), Height);
		AreaEffect->SetColorParameter(FName("Color"), Color);
	}
}

// Called when the game starts or when spawned
void AHCT26TeslaTower::BeginPlay()
{
	Super::BeginPlay();
	
	// Cache the player's pawn
	if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		CachedPlayerPawn = PlayerController->GetPawn();
	}
	
}

void AHCT26TeslaTower::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateAreaEffectParameters(200.f, 
								200.f, 
								FLinearColor::FromSRGBColor(FColor(255, 0, 0)));
}

// Called every frame
void AHCT26TeslaTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ShootEffect != nullptr && CachedPlayerPawn != nullptr)
	{
		ShootEffect->SetVariablePosition(FName("PositionTarget"), CachedPlayerPawn->GetActorLocation());
	}
}

