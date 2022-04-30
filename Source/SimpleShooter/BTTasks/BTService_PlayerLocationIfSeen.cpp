// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

class AAIShooterCharacter;

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "UpdPlayerLocIfSeen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Get Player Pawn
	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) { return; }

	//Get AI Controller
	auto AICtrl = OwnerComp.GetAIOwner();
	if (AICtrl == nullptr) { return; }

	AAIShooterCharacter* AICharacter = Cast<AAIShooterCharacter>(AICtrl->GetPawn());
	
	auto ShooterAICtrl = Cast<AShooterAIController>(AICharacter->GetController());
	if (ShooterAICtrl == nullptr) { UE_LOG(LogTemp, Warning, TEXT("Print null CTRL")); return; }

	
	if(ShooterAICtrl->IsPlayerSeen())
	{
		AICtrl -> GetBlackboardComponent() -> SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else
	{
		// AICtrl -> ClearFocus(EAIFocusPriority::Gameplay);
		// AICtrl -> GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}


//AAIShooterCharacter* AICharacter = Cast<AAIShooterCharacter>(AICtrl->GetPawn());

// if(AICtrl -> LineOfSightTo(PlayerPawn))
// {
// 	FVector PlayerLocation = PlayerPawn -> GetActorLocation();
// 	AICtrl -> GetBlackboardComponent() -> SetValueAsVector(GetSelectedBlackboardKey(), PlayerLocation);
// }
// else
// {
// 	AICtrl -> ClearFocus(EAIFocusPriority::Gameplay);
// 	AICtrl -> GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
// }
