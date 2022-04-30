#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateState.generated.h"

/**
 * 
 */
UCLASS()
class UBTService_UpdateState : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_UpdateState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
