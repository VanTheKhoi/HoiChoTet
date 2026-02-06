// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "HCT26ButtonBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignatureStartOverlap, AActor*, OverlappingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignatureEndOverlap, AActor*, OverlappingActor);

UCLASS()
class HCT26_API AHCT26ButtonBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCT26ButtonBase();
	
	UPROPERTY(BlueprintAssignable, Category=HoiChoTet)
	FSignatureStartOverlap StartOverlap;
	
	UPROPERTY(BlueprintAssignable, Category=HoiChoTet)
	FSignatureEndOverlap EndOverlap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> CollisionComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

};
