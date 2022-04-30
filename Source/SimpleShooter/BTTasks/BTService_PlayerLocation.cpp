// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = "PlayerLastLocation";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	//Get Player Pawn
	auto PlayerChar = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(PlayerChar)
	{
		FVector PlayerLocation = PlayerChar -> GetActorLocation();
		OwnerComp.GetAIOwner() -> GetBlackboardComponent() -> SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
	}
	
}
