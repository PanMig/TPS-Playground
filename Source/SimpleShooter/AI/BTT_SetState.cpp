#include "BTT_SetState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

UBTT_SetState::UBTT_SetState()
{
	NodeName = "SetNPCState";
}

EBTNodeResult::Type UBTT_SetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(OwnerComp.GetAIOwner() == nullptr) {	return EBTNodeResult::Failed; }

	auto AICtrl = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (AICtrl == nullptr) { return EBTNodeResult::Failed; }

	AICtrl->SetNPCState(StateToSet);
	UE_LOG(LogTemp, Warning, TEXT("Output: Succedeed in state") );

	return EBTNodeResult::Succeeded;
}


