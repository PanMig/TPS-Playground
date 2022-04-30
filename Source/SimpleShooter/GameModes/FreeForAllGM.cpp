// Fill out your copyright notice in the Description page of Project Settings.


#include "FreeForAllGM.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

void AFreeForAllGM::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);
	
	UE_LOG(LogTemp, Warning, TEXT("Pawn Killed"));

	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if(PlayerController != nullptr)
	{
		EndGame(false);
	}

	for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!Controller -> IsDead()){ return; }		
	}

	EndGame(true);
}

void AFreeForAllGM::EndGame(bool bIsPlayerWinner)
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller -> IsPlayerController() == bIsPlayerWinner;
		Controller -> GameHasEnded(Controller -> GetPawn(), bIsPlayerWinner);
	}
}
