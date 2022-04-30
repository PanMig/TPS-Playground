// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_GetToCover.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

class AShooterCharacter;

UBTS_GetToCover::UBTS_GetToCover()
{
	NodeName = "GetToCover";
}

EBTNodeResult::Type UBTS_GetToCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr) {	return EBTNodeResult::Succeeded; }
	
	auto AICtrl = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (AICtrl == nullptr) { return EBTNodeResult::Succeeded; }

	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AIPawn != nullptr)
	{
		TArray<AActor*> CoverSpots;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(),TEXT("CoverSpot"), CoverSpots);
		if(CoverSpots.Num() > 0)
		{
			AICtrl->MoveToLocation(CoverSpots[0]->GetActorLocation(),50);
			AICtrl->SetFocus(CoverSpots[0]);
		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("No covers"));
		}
		
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
}


