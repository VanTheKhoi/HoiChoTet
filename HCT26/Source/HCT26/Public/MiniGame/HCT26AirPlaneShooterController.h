// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Interaction/HCT26AirPlaneShooterButton.h"
#include "HCT26AirPlaneShooterController.generated.h"

UCLASS()
class HCT26_API AHCT26AirPlaneShooterController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCT26AirPlaneShooterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Scene Root
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneRoot;
	
	// Player Pawn Class Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
	TSubclassOf<APawn> PlayerPawnClass;
	
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	// Player Spawn Point
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> PlayerSpawnPoint;
	
	// Enemy Spawn Point
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> EnemySpawnPoint;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Reference to broadcaster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Listener")
	AHCT26AirPlaneShooterButton* Broadcaster;
	
	UFUNCTION()
	void StartAirPlaneShooterGame(bool IsStartGame);
	
	// Spawn player function
	UFUNCTION()
	void SpawnPlayer();
};
