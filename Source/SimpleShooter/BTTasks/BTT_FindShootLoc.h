// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindShootLoc.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTT_FindShootLoc : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTT_FindShootLoc();
protected:
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
