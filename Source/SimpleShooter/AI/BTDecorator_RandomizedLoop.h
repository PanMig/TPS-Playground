// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Loop.h"
#include "BTDecorator_RandomizedLoop.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTDecorator_RandomizedLoop : public UBTDecorator_Loop
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 LowerRndBound;

	UPROPERTY(EditAnywhere)
	int32 UpperRndBound;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
};
