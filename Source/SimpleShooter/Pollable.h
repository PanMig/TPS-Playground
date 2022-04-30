// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Pollable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPollable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLESHOOTER_API IPollable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetTransformation(const FVector& Position, const FRotator& Rotation);
	virtual void Activate();
	virtual void Deactivate();
	virtual bool IsInUse(const AActor* PollableActor);
};
