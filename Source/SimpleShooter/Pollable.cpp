// Fill out your copyright notice in the Description page of Project Settings.


#include "Pollable.h"

// Add default functionality here for any IPollable functions that are not pure virtual.
void IPollable::SetTransformation(const FVector& Position, const FRotator& Rotation)
{
}

void IPollable::Activate()
{
}

void IPollable::Deactivate()
{
}

bool IPollable::IsInUse(const AActor* PollableActor)
{
	return PollableActor->IsHidden();
}
