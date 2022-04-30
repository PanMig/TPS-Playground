#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "SniperBotController.generated.h"

struct FPathFollowingResult;

UCLASS()
class SIMPLESHOOTER_API ASniperBotController: public AShooterAIController
{
	GENERATED_BODY()
public:
	ASniperBotController();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AAIShooterCharacter* SniperCharacter;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
