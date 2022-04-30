// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_ActorsOfClass.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_SimpleGrid.h"
#include "EnvQueryGenerator_CoverInZone.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UEnvQueryGenerator_CoverInZone : public UEnvQueryGenerator_ProjectedPoints
{
	GENERATED_BODY()
protected:
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CoverSpotClass;

	UPROPERTY(EditAnywhere)
	int32 DistBetweenPoints = 200.0f;
	UPROPERTY(EditAnywhere)
	int32 GridHalfExtend = 300.0f;
};
