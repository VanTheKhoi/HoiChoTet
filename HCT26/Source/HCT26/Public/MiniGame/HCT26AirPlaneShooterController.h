// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AirPlaneShooter Controller|Spawn")
	TSubclassOf<APawn> PlayerSPawnClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AirPlaneShooter Controller|Spawn")
	TSubclassOf<APawn> EnemySpawnClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AirPlaneShooter Controller|Gameplay")
	bool bIsCameraShaking;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AirPlaneShooter Controller|Gameplay")
	TSubclassOf<UUserWidget> WidgetClass;
	
	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	// Player Spawn Point
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> PlayerSpawnPoint;
	
	// Enemy Spawn Point
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> EnemySpawnPoint;
	
	UPROPERTY()
	class AHCT26AirPlaneShooterPlayerBase* PlayerBase;
	
	UPROPERTY()
	class AHCT26AirPlaneShooterButton* Broadcaster;
	
	UPROPERTY()
	class UHCT26AirPlaneShooterGameMenuBase* GameMenu;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY()
	int32 EnemySpawnCount;
	
	UPROPERTY()
	int32 EnemyToSpawn;
	
	UPROPERTY()
	UUserWidget* MainMenuWidget;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void StartAirPlaneShooterGame(bool IsStartGame);
	
	UFUNCTION()
	void PlayAirPlaneShooterGame();
	
	// Spawn player function
	UFUNCTION()
	void SpawnPlayer();
	
	// Spawn enemy function
	UFUNCTION()
	void SpawnEnemy();
	
	UFUNCTION()
	void SpawnNextEnemy();
	
	// Camera shake function
	UFUNCTION()
	void CameraShake(bool IsPlayerDead);
};
