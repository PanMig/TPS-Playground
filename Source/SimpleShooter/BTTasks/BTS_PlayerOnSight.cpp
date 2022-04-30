// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_PlayerOnSight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

UBTS_PlayerOnSight::UBTS_PlayerOnSight()
{
	NodeName = "SetPlayerOnSight";
}

void UBTS_PlayerOnSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto AICtrl = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (AICtrl == nullptr) { return; }

	if(AICtrl->IsPlayerSeen())
	{
		AICtrl -> GetBlackboardComponent() -> SetValueAsObject("Player", UGameplayStatics::GetPlayerPawn(GetWorld(),0));		
		AICtrl -> GetBlackboardComponent() -> SetValueAsBool(GetSelectedBlackboardKey(), true);		
	}
	// else
	// {
	// 	AICtrl -> GetBlackboardComponent() -> SetValueAsObject("Player", nullptr);		
	// 	AICtrl -> GetBlackboardComponent() -> SetValueAsBool(GetSelectedBlackboardKey(), false);		
	// }
}
