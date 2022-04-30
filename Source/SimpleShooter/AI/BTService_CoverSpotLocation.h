#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CoverSpotLocation.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_CoverSpotLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class ACoverVolume* ClosestSpot = nullptr;

public:
	UBTService_CoverSpotLocation();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
