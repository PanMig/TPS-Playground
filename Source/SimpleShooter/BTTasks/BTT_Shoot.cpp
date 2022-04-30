// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Shoot.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "AIController.h"

UBTT_Shoot::UBTT_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTT_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr) {	return EBTNodeResult::Succeeded; }

	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AIPawn != nullptr)
	{
		AIPawn->Shoot();
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
	
}
