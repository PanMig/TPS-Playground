// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "UBTTask_GetPatrolLocation.generated.h"

class UNavigationSystemV1;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_GetPatrolLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UNavigationSystemV1* NavSystem;

protected:
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_GetPatrolLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 1000;

	int CurrPatrolIdx = 0;
	
};
