// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultBotController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"


// Sets default values
AAssaultBotController::AAssaultBotController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAssaultBotController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(BlackboardToUse)) { return; } // We ensure that pointer isn't null
	UseBlackboard(BlackboardToUse, BlackboardComp);

	if (!ensure(BehaviorTree)) { return; } // We ensure that BehaviorTree isn't null

	// Run the behavior tree
	RunBehaviorTree(BehaviorTree);

	NPCState = ENPCState::Patrolling;
	BlackboardComp->SetValueAsVector("LastPlayerLocation",ControlledCharacter->GetActorLocation());
}

// Called every frame
void AAssaultBotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsPlayerSeen() && NPCState == ENPCState::Patrolling || ControlledCharacter->GetIsHit())
	{
		NPCState = ENPCState::AlertedLOF;
	}

	switch (NPCState)
	{
	case ENPCState::Patrolling:
		ControlledCharacter->bUseControllerRotationYaw = false;
		ControlledCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		ControlledCharacter->SetMovementSpeed(ControlledCharacter->WalkSpeed);
		break;
	case ENPCState::AlertedLOF:
		ControlledCharacter->bUseControllerRotationYaw = true;
		ControlledCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		ControlledCharacter->SetMovementSpeed(ControlledCharacter->JogSpeed);
		break;
	default:
		break;
	}
}

void AAssaultBotController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
}
