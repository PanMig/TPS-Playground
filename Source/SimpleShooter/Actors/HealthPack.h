// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectablesBase.h"
#include "HealthPack.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AHealthPack : public ACollectablesBase
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
	float HealthIncrease = 100.0f;

public:
	virtual void BeginPlay() override;

	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
