#include "SniperBotController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"

// Sets default values
ASniperBotController::ASniperBotController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

// Called when the game starts or when spawned
void ASniperBotController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(BlackboardToUse)) { return; } // We ensure that pointer isn't null
	UseBlackboard(BlackboardToUse, BlackboardComp);
	
	if (!ensure(BehaviorTree)) { return; }// We ensure that BehaviorTree isn't null
	
	// Run the behavior tree
	RunBehaviorTree(BehaviorTree);

	NPCState = ENPCState::Patrolling;

	SniperCharacter = Cast<AAIShooterCharacter>(GetPawn());
	if(!ensure(SniperCharacter)) {UE_LOG(LogTemp, Warning, TEXT("Output: Error, sniper character is null"));}

}

void ASniperBotController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(SniperCharacter->bIsHit)
	{
		SetFocus(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	}
	
	switch (NPCState)
	{
	case 0:
		if (IsPlayerSeen())
		{
			NPCState = ENPCState::Alerted;
		}
		break;
	case 1:
		if(SniperCharacter->IsCovering())
		{
			NPCState = ENPCState::Covered;
		}
		break;
	case 2:
		if(!IsPlayerSeen())
		{
			NPCState = ENPCState::OnGuard;
		}
		break;
	case 3:
		if(IsPlayerSeen())
		{
			NPCState = ENPCState::Covered;
		}
		break;
	default:
		break;
	}
		
}

void ASniperBotController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}
