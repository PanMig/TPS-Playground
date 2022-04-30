// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryGenerator_CoverInZone.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

void UEnvQueryGenerator_CoverInZone::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> QueryItems;
	auto AIPawn = Cast<AAIShooterCharacter>((QueryInstance.Owner).Get());
	if(AIPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Output: EMPTY CONTROLLER IN EQS_CoverInZone"));
		return;
	}

	auto CombatZone = AIPawn-> GetCombatZoneVolume();
	if(!ensure(CombatZone)) return;
	
	auto CombatZoneBounds = CombatZone->GetBounds();
	
	
	TArray<AActor*> CoverSpots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CoverSpotClass, CoverSpots);
	for (auto CoverSpot : CoverSpots)
	{
		auto CoverLoc = CoverSpot->GetActorLocation();
		auto bInZone = UKismetMathLibrary::IsPointInBox(CoverLoc, CombatZoneBounds.Origin, CombatZoneBounds.BoxExtent);
		if(bInZone)
		{
			//calculate bottom left point
			auto BL = CoverLoc - FVector(GridHalfExtend, GridHalfExtend, 0);
			//DrawDebugLine(GetWorld(),BL,BL+ FVector(0,0,DistBetweenPoints),FColor::Red,false,100.0f);
			for(int stepX = 0; stepX <= GridHalfExtend*2; stepX+=DistBetweenPoints)
			{
				for(int stepY = 0; stepY <= GridHalfExtend*2; stepY+=DistBetweenPoints)
				{
					auto NavPoint = FNavLocation(FVector(BL.X + stepX, BL.Y + stepY, BL.Z ));
					if(UKismetMathLibrary::IsPointInBox(NavPoint.Location, CombatZoneBounds.Origin, CombatZoneBounds.BoxExtent))
					{
						QueryItems.Add(NavPoint);
					}
				}
			}
		}
	}
	

	//Projects all the nav points into our Viewport and removes those outside of our navmesh
	ProjectAndFilterNavPoints(QueryItems, QueryInstance);

	//Store the generated points as the result of our Query
	StoreNavPoints(QueryItems, QueryInstance);
}

FText UEnvQueryGenerator_CoverInZone::GetDescriptionTitle() const
{
	return FText::FromString("Generate grid of points around cover spots in zone of the AI owner");
}
