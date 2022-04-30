// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BBoardClearValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BBoardClearValue::UBTTask_BBoardClearValue()
{
	NodeName = TEXT("Clear BBoard Value");	
}

EBTNodeResult::Type UBTTask_BBoardClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Get backboard and clear selected key
	OwnerComp.GetBlackboardComponent() -> ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
