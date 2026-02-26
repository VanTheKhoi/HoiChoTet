// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "InputActionValue.h"
#include "HCT26AirPlaneShooterPlayerBase.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class HCT26_API AHCT26AirPlaneShooterPlayerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHCT26AirPlaneShooterPlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Input actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> AirPlaneShooterPlayerMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_AirPlaneShooterPlayerShoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> IA_AirPlaneShooterPlayerMovement;
	
	// Player health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerSetup|Health")
	float Health = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerSetup|Movement")
	float MoveSpeed = 100.0f;
	
	// Reference to bullet class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerSetup|Bullet")
	TSubclassOf<AActor> BulletClass;
	
	// Exploision Particle System
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerSetup|Effects")
	TObjectPtr<UParticleSystem> ExplosionParticleSystem;
	
	// Is Spawn Explosion Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerSetup|Effects")
	bool bSpawnExplosionEffect;
	
	// Scene Root
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneRoot;
	
	// Airplane Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> AirPlaneMesh;
	
	// Particle system
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	TObjectPtr<UParticleSystemComponent> AirPlaneParticleSystem;
	
	// Sphere Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> CollisionComponent;
	
	// Function to handle hit events
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			   const FHitResult& Hit);
	
	UFUNCTION()
	virtual void Shoot(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void Movement(const FInputActionValue& Value);
};
