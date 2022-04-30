// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"

AShooterAIController::AShooterAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIEyes"));
	SetPerceptionComponent(*AIPerceptionComponent);
	
	// Assign to Team 1
	SetGenericTeamId(FGenericTeamId(1));
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Running Parent Begin play"));
	
	//Set PerceptionUpdated delegate.
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AShooterAIController::OnSightUpdated);
	
	//Get Player Pawn
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	//Controlled Character
	ControlledCharacter = Cast<AAIShooterCharacter>(GetPawn());
	if(!ControlledCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Output: Controlled pawn in %s is null"), *this->GetName());
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AShooterAIController::IsDead() const
{
	// if(ControlledAICharacter != nullptr)
	// {
	// 	return ControlledAICharacter -> IsDead();
	// }

	return true;
}

bool AShooterAIController::IsPlayerSeen() const
{
	return bPlayerSeen;
}

void AShooterAIController::OnSightUpdated(const TArray<AActor*>& UpdatedActors)
{
	if(bPlayerSeen)
	{
		bPlayerSeen = false;
		BlackboardComp->SetValueAsBool("IsPlayerOnSight", bPlayerSeen);
	}
	else
	{
		bPlayerSeen = true;
		BlackboardComp->SetValueAsBool("IsPlayerOnSight", bPlayerSeen);
	}
}

FVector AShooterAIController::GetShootingPositionFrom(AActor* TargetActor, float Radious)
{	
	TArray<FVector> AroundPoints;
	const auto TargetLoc = TargetActor->GetActorLocation();
	for(int i = 0; i < 360; i+=30)
	{
		auto Position = FVector(Radious*cos(i * PI / 180.0), Radious*sin(i * PI / 180.0), TargetLoc.Z);
		Position += TargetLoc;
		DrawDebugSphere(GetWorld(),Position,20,5,FColor::Red,false,5);
		AroundPoints.Emplace(Position);
	}

	int idx = FMath::RandRange(0,AroundPoints.Num()-1);
	return AroundPoints[idx];
	
}

void AShooterAIController::FindShootingSpot()
{	
	if(FindShootingSpotEQS != nullptr)
	{
		FEnvQueryRequest ShootingSpotQueryRequest = FEnvQueryRequest(FindShootingSpotEQS, UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		ShootingSpotQueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &AShooterAIController::MoveToQueryResult);
	}
}

void AShooterAIController::MoveToQueryResult(TSharedPtr<FEnvQueryResult> result)
{
	// if (result->IsSuccsessful() && result->Items.Num() > 0) {
	// 	
	// 	for(int i = 0; i < result->Items.Num(); i++)
	// 	{
	// 		auto itemLoc = result->GetItemAsLocation(i);
	// 		
	// 		//Shoot LineTrace from Point to Player
	// 		FHitResult Hit;
	// 		FVector Start = itemLoc;
	// 		FVector End = UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorLocation();
	// 		FCollisionQueryParams CollisionParams;
	// 		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldDynamic, CollisionParams);
	//
	// 		//Move to location if player is visible from point.
	// 		if(Hit.GetActor() && Hit.GetActor()->Tags[0] == TEXT("Player"))
	// 		{
	// 			MoveTo(result->GetItemAsLocation(i));
	// 			return;
	// 		}
	// 	}
	// 	
	// }
}
