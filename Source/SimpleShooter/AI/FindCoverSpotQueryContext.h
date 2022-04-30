// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "FindCoverSpotQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UFindCoverSpotQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
