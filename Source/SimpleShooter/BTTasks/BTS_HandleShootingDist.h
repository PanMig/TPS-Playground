// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_HandleShootingDist.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTS_HandleShootingDist : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTS_HandleShootingDist();
	
	UPROPERTY(EditAnywhere)
	float Range;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
