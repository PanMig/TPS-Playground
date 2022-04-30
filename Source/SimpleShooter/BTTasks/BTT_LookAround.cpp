// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_LookAround.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Actor origin
	AShooterCharacter* AIPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AIPawn == nullptr) { return EBTNodeResult::Succeeded; }

	FRotator RotateAmount = FRotator(0,Angle, 0);
	AIPawn->AddActorLocalRotation(RotateAmount);

	return EBTNodeResult::Succeeded;
}

UBTT_LookAround::UBTT_LookAround()
{
	NodeName = "LookAround";
}
