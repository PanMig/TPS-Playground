// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Crouch.h"
#include "AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

EBTNodeResult::Type UBTTask_Crouch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr) {	return EBTNodeResult::Succeeded; }

	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AIPawn != nullptr)
	{
		AIPawn->CrouchAction();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
	
}

UBTTask_Crouch::UBTTask_Crouch()
{
	NodeName = "Crouch";
}


