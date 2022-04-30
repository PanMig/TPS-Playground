#include "BTService_CoverSpotLocation.h"

#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Actors/CoverVolume.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"
#include "SimpleShooter/Actors/CoverVolume.h"
#include "SimpleShooter/Controllers/AssaultBotController.h"

UBTService_CoverSpotLocation::UBTService_CoverSpotLocation()
{
	NodeName = "FindClosestCoverLocation";
}

void UBTService_CoverSpotLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto AICtrl = Cast<AAIController>(OwnerComp.GetAIOwner());
	auto AssaultBotCtrl = Cast<AAssaultBotController>(AICtrl);
	if (OwnerComp.GetAIOwner() == nullptr || AICtrl == nullptr)
	{
		return;
	}

	AssaultBotCtrl->OnNewCoverSpotLocation.BindLambda([=]()
	{
		AssaultBotCtrl->SetNPCState(ENPCState::AlertedLOF);
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White,
		                                 FString::Printf(
			                                 TEXT("Output: Changed location")));
	});
	
	
	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIPawn != nullptr)
	{
		TArray<AActor*> CoverSpots;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoverVolume::StaticClass(), CoverSpots);

		//AI cached data
		auto AILoc = AIPawn->GetActorLocation();
		//Player cached data
		auto PlayerLoc = PlayerPawn->GetActorLocation();

		TMap<AActor*, float> ShootingSpots;
		for (auto Spot : CoverSpots)
		{
			float Score = 0.0f;
			// calculate dot product with player
			auto PlayerToCoverDist = PlayerLoc - Spot->GetActorLocation();
			PlayerToCoverDist.Normalize();
			auto DotProduct = FVector::DotProduct(Spot->GetActorForwardVector(), PlayerToCoverDist);
			Score += DotProduct * 10.0f;

			//caluculate distance to self
			auto CoverLoc = Spot->GetActorLocation();
			auto DistFromSelf = FVector::Dist(AILoc, CoverLoc);
			Score += DistFromSelf * -10.0f;

			//Add to Map
			ShootingSpots.Add(Spot, Score);
		}

		// Sort with decending order
		ShootingSpots.ValueSort([](const float a, const float b) { return a > b; });
		if (ShootingSpots.Num() > 0)
		{
			CoverSpots.Empty();
			ShootingSpots.GenerateKeyArray(CoverSpots);
			ClosestSpot = Cast<ACoverVolume>(CoverSpots[0]);
			if(AssaultBotCtrl->CurrentCoverSpot != ClosestSpot)
			{
				AssaultBotCtrl->OnNewCoverSpotLocation.Execute();
				AssaultBotCtrl->CurrentCoverSpot = ClosestSpot;
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
															 ClosestSpot->GetCoverSpotLocation());
	}
}
