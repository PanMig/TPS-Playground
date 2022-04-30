#include "BTService_UpdateState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

UBTService_UpdateState::UBTService_UpdateState()
{
	NodeName = "UpdateState";
}

void UBTService_UpdateState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto AICtrl = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	
	if(OwnerComp.GetAIOwner() == nullptr || AICtrl == nullptr)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum( GetSelectedBlackboardKey(), (uint8) AICtrl->GetNPCState());
}

