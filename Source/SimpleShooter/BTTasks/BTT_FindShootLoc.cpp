// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindShootLoc.h"


#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/AIShooterCharacter.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

UBTT_FindShootLoc::UBTT_FindShootLoc()
{
	NodeName = "FindShootLoc";
}

EBTNodeResult::Type UBTT_FindShootLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AICtrl = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	if (AICtrl == nullptr) { return EBTNodeResult::Succeeded; }

	auto NPCCharacter = Cast<AAIShooterCharacter>(AICtrl->GetPawn());
	if (NPCCharacter == nullptr) { return EBTNodeResult::Succeeded; }

	auto PLayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (PLayerPawn == nullptr) { return EBTNodeResult::Succeeded; }

	//AICtrl->FindShootingSpot();

	return EBTNodeResult::Succeeded;
}
