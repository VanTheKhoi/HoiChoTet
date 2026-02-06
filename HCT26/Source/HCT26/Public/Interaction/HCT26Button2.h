// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HCT26ButtonBase.h"
#include "NiagaraFunctionLibrary.h"
#include "HCT26Button2.generated.h"

UCLASS()
class HCT26_API AHCT26Button2 : public AHCT26ButtonBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHCT26Button2();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="HoiChoTet|FX_Overlap")
	TObjectPtr<UNiagaraSystem> OverlapEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void ExecuteFXOverlap(AActor* OverlappingActor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
