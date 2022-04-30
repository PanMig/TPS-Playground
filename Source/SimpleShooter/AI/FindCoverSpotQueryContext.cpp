// Fill out your copyright notice in the Description page of Project Settings.


#include "FindCoverSpotQueryContext.h"

#include "AIController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Actors/CoverVolume.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

void UFindCoverSpotQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	auto AICtrl = Cast<AAIController>(QueryInstance.Owner);
	
	if(QueryInstance.Owner == nullptr || AICtrl == nullptr)
	{
		return;
	}
	
	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(AICtrl->GetPawn());
	
	TArray<AActor*> CoverSpots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoverVolume::StaticClass(), CoverSpots);
	if(CoverSpots.Num() > 0)
	{
		//find closest cover to player
		auto Min = 500000000;
		auto PlayLoc = AIPawn->GetActorLocation();
		ACoverVolume* ClosestSpot;
		for (const auto C : CoverSpots)
		{
			auto CoverSpot = Cast<ACoverVolume>(C);
			//if (!ensure(CoverSpot) || !CoverSpot->IsOccupied()) { continue;; }

			// cover location is taken by another bot
			if(CoverSpot->IsOccupied()) continue;
				
			auto CoverLoc = CoverSpot->GetActorLocation();
			auto Dist = FVector::Dist(PlayLoc, CoverLoc);
			if(Min > Dist)
			{
				Min = Dist;
				ClosestSpot = Cast<ACoverVolume>(CoverSpot);
				UEnvQueryItemType_Actor::SetContextHelper(ContextData, ClosestSpot);
			};
		}
	}
}
