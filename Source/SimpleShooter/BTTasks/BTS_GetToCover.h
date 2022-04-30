// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTS_GetToCover.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTS_GetToCover : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UBTS_GetToCover();

	
};
