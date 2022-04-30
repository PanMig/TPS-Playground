// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTTask_GetPatrolLocation.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"
#include <random>

UBTTask_GetPatrolLocation::UBTTask_GetPatrolLocation()
{
	NodeName = TEXT("GetPatrolPoint");
}

EBTNodeResult::Type UBTTask_GetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Actor origin
	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AIPawn == nullptr) { return EBTNodeResult::Failed; }
	
	//FVector Origin = AIPawn->GetActorLocation();
	
	//Get random point in Navigable radius
	// FVector RandomLocation;
	// NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	// if(NavSystem == nullptr) { return EBTNodeResult::Succeeded; }

	 //Get Random map location
	 // FNavLocation NavLocation;
	 // const bool bGetRandomPoint = NavSystem->GetRandomReachablePointInRadius(Origin, Radius, NavLocation);
	 // if(bGetRandomPoint)
	 // {
	 // 	//Set blackboard value
	 // 	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
	 // }

	//Get patrol point location

	AAIShooterCharacter* AIChar = Cast<AAIShooterCharacter>(AIPawn);
	if(AIChar != nullptr)
	{
		if (AIChar->PatrolPoints.IsEmpty()) {return EBTNodeResult::Failed;}
		
		CurrPatrolIdx = CurrPatrolIdx % AIChar-> PatrolPoints.Num();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("PatrolLocation", AIChar->PatrolPoints[CurrPatrolIdx]);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			CurrPatrolIdx++;
		}, 1.0f, false);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
	
}


