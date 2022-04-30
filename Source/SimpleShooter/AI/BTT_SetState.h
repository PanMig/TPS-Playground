#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"
#include "BTT_SetState.generated.h"
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTT_SetState : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
public:
	UPROPERTY(EditAnywhere)
	UBlackboardKeyType* SelectedKey;
	
	UPROPERTY(EditAnywhere)
	ENPCState StateToSet;
	
	UBTT_SetState();
};
