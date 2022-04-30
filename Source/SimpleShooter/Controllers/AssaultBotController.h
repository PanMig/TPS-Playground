// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShooterAIController.h"
#include "AssaultBotController.generated.h"

UCLASS()
class SIMPLESHOOTER_API AAssaultBotController : public AShooterAIController
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE(FOnNewCoverSpotLocation);
public:
	AAssaultBotController();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY()
	class ACoverVolume* CurrentCoverSpot;

	FOnNewCoverSpotLocation OnNewCoverSpotLocation;
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
