// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "HCT26AirPlaneShooterEnemyBase.generated.h"

UCLASS()
class HCT26_API AHCT26AirPlaneShooterEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHCT26AirPlaneShooterEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	bool bIsEnemyDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
	bool bIsSuicide;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySetup|Movement")
	float MoveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySetup|Health")
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySetup|Effects")
	TObjectPtr<UParticleSystem> ExplosionParticleSystem;
	
	UPROPERTY()
	bool bIsStopMovement;
	
	UPROPERTY()
	FVector CurrentVelocity;
	
	UPROPERTY()
	bool bSpawnExplosionEffect;
	
	UPROPERTY()
	FTimerHandle DelayTimerHandle;
	
	UPROPERTY()
	FLinearColor OriginalColor;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Scene Root
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneRoot;
	
	// Airplane Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> AirPlaneMesh;
	
	// Sphere Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> CollisionComponent;

	UFUNCTION()
	void RandomDirection();
	
	UFUNCTION()
	void MoveLeftRight(float DeltaTime);
	
	UFUNCTION()
	void EnemyDeath();
	
	UFUNCTION()
	void EnemySuicide(float DeltaTime);
	
	UFUNCTION()
	void CreateAndApplyDMI(FLinearColor Color, FName ParameterName);
	
	UFUNCTION()
	void Damaged();
	
	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
	
};
