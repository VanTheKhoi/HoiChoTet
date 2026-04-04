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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AirPlaneShooter Controller|Gameplay")
	TSubclassOf<UUserWidget> GameMainMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AirPlaneShooter Controller|Gameplay")
	TSubclassOf<UUserWidget> GameOverMenu;
	
	UPROPERTY()
	APawn* DefaultPawn;
	
	// Input actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AirPlaneShooter Controller|Input")
	class UInputMappingContext* DefaultMappingContext;
	
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
	class AHCT26AirPlaneShooterButton* Broadcaster;
	
	UPROPERTY()
	class AHCT26MainPlayerBase* DefaultPawnCast;
	
	UPROPERTY()
	APlayerController* PlayerController;
	
	UPROPERTY()
	class AHCT26AirPlaneShooterPlayerBase* PlayerBaseCast;
	
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY()
	FTimerHandle DelayHandle;
	
	UPROPERTY()
	int32 EnemySpawnCount;
	
	UPROPERTY()
	int32 EnemyToSpawn;
	
	UPROPERTY()
	UUserWidget* MainMenuWidget;
	
	UPROPERTY()
	UUserWidget* GameOverWidget;
	
	UPROPERTY()
	TArray<APawn*> Enemies;
	
	UPROPERTY()
	APawn* SpawnedPlayer;
	
	UPROPERTY()
	class UEnhancedInputLocalPlayerSubsystem* Subsystem;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void StartAirPlaneShooterGame(bool IsStartGame);
	
	UFUNCTION()
	void PlayAirPlaneShooterGame();
	
	UFUNCTION()
	void QuitAirPlaneShooterGame();
	
	UFUNCTION()
	void SpawnPlayer();
	
	UFUNCTION()
	void SpawnEnemy();
	
	UFUNCTION()
	void SpawnNextEnemy();
	
	UFUNCTION()
	void PlayerDead(bool IsPlayerDead);
};
