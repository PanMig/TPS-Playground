// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_LookAround.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTT_LookAround : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTT_LookAround();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Angle;
};
