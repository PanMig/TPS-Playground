// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"
#include "FreeForAllGM.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AFreeForAllGM : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* KilledPawn) override;
	void EndGame(bool bIsPlayerWinner);
};
