// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameplayTagContainer.h"
#include "HCT26AirPlaneShooterBulletBase.generated.h"

UCLASS()
class HCT26_API AHCT26AirPlaneShooterBulletBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCT26AirPlaneShooterBulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Bullet Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> BulletMesh;
	
	// Scene Root
	UPROPERTY()
	TObjectPtr<USceneComponent> SceneRoot;
	
	// Sphere Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> CollisionComponent;
	
	// Project tile movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	// Bullet speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet Setup")
	float BulletSpeed = 500.0f;
	
	// Bullet destroy time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet Setup")
	float DestroyTime = 1.5f;
	
	// Bullet damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet Setup")
	float Damage = 20.0f;
	
	// Gameplay tags for the bullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet Setup")
	FGameplayTagContainer TagContainer;
	
	UPROPERTY()
	FTimerHandle DestroyTimerHandle;
	
	// Function to handle hit events
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse,
			   const FHitResult& Hit);
};
