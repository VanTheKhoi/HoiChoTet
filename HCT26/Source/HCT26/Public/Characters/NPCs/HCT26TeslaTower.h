// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/MeshComponent.h"
#include "HCT26TeslaTower.generated.h"

UCLASS()
class HCT26_API AHCT26TeslaTower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHCT26TeslaTower();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=VFX)
	TObjectPtr<UNiagaraComponent> ShootEffect;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=VFX)
	TObjectPtr<UNiagaraComponent> AreaEffect;
	
	UFUNCTION(BlueprintCallable, Category=TeslaTower)
	void UpdateAreaEffectParameters(float Radius, float Height, FLinearColor Color);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Cached reference to the player pawn
	UPROPERTY(BlueprintReadOnly, Category=Player)
	TObjectPtr<APawn> CachedPlayerPawn;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
