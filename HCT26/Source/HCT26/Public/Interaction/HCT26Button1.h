// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HCT26ButtonBase.h"
#include "NiagaraFunctionLibrary.h"
#include "HCT26Button1.generated.h"

UCLASS()
class HCT26_API AHCT26Button1 : public AHCT26ButtonBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCT26Button1();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="HoiChoTet|FX_Overlap")
	TObjectPtr<UNiagaraSystem> OverlapEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult) override;
	
	virtual void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex) override;
};
