// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_HandleShootingDist.h"



#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

UBTS_HandleShootingDist::UBTS_HandleShootingDist()
{
	NodeName = "HandleShootingDist";
}

void UBTS_HandleShootingDist::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto AICtrl = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (AICtrl == nullptr) { return; }

	auto NPCCharacter = Cast<AAIShooterCharacter>(AICtrl->GetPawn());
	if (NPCCharacter == nullptr) { return; }

	auto PLayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (PLayerPawn == nullptr) { return; }
	
	//Check if too close to the player
	auto DistToPlayer = NPCCharacter->GetDistanceTo(PLayerPawn);

	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if(DistToPlayer <= 300)
	{
		//AICtrl->SetHasShootingSpot(false);
		
		//Ad hoc method
		//auto ShootingPos = AICtrl->GetShootingPositionFrom(PLayerPawn, Range);
		//AICtrl->MoveTo(ShootingPos);
		
		//EQS query for shooting spot
		//AICtrl->FindShootingSpot();

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Close"));	
	}
	
}


