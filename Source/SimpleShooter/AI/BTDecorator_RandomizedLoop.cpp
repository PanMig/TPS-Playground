// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_RandomizedLoop.h"

UBTDecorator_RandomizedLoop::UBTDecorator_RandomizedLoop(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer), LowerRndBound(0), UpperRndBound(1)
{
	NodeName = "RandomizedLoop";
}

void UBTDecorator_RandomizedLoop::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	NumLoops = FMath::RandRange(LowerRndBound, UpperRndBound);
	Super::OnNodeActivation(SearchData);
}
