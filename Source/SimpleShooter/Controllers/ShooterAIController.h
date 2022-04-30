// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Engine/TriggerVolume.h"
#include "ShooterAIController.generated.h"

class AAIShooterCharacter;
class UAISenseConfig_Sight;
class AIPerceptionComponent;
struct FEnvQueryResult;
class UEnvQuery;


UENUM(BlueprintType)
enum class ENPCState : uint8{
	Patrolling UMETA(DisplayName = "Patrolling"), // stand idle and wait
	Alerted UMETA(DisplayName = "Alerted"), // take action to hide from player
	AlertedLOF UMETA(DisplayName = "AlertedLOF"), // take action to hide from player
	AlertedNLOF UMETA(DisplayName = "AlertedNLOF"), // take action to hide from player
	Covered UMETA(DisplayName = "Covered"), // in cover with focus on the player
	OnGuard UMETA(DisplayName = "OnGuard"), // searching for player
	Searching UMETA(DisplayName = "Searching")
};

UCLASS(config=Game)
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	UEnvQuery* FindShootingSpotEQS;

	bool bHasShootingSpot;

	FVector GetShootingPositionFrom(AActor* FromActor, float Radious);
	
	void FindShootingSpot();
	
	void MoveToQueryResult(TSharedPtr<FEnvQueryResult> result);

	bool HasShootingSpot() const
	{
		return bHasShootingSpot;
	}
	void SetHasShootingSpot(bool value)
	{
		bHasShootingSpot = value;
	}
protected:
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShooterAI")
	UBehaviorTree* BehaviorTree;
 
	/*Blackboard comp ref*/
	UPROPERTY(EditDefaultsOnly, Category = "ShooterAI")
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = "ShooterAI")
	UBlackboardData* BlackboardToUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCState NPCState;
	
	UPROPERTY()
	APawn* PlayerPawn = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	AAIShooterCharacter* ControlledCharacter;
	
	bool bPlayerSeen = false;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void OnSightUpdated(const TArray<AActor*>& UpdatedActors);
public:
	AShooterAIController();
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
	bool IsPlayerSeen() const;
	
	ENPCState GetNPCState() const
	{
		return NPCState;
	}

	void SetNPCState(ENPCState Value)
	{
		NPCState = Value;
	}
};
