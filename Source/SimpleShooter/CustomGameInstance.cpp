// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "Pollable.h"
#include "Actors/ProjectileBase.h"

void UCustomGameInstance::OnStart()
{
	Super::OnStart();

	InitPool();
}

AActor* UCustomGameInstance::GetPooledObject()
{
	for(int i = 0; i < Max_Pool_Size; i++)
	{
		auto PollableActor = Cast<IPollable>(BulletsPool[i]);
		if(!PollableActor)
		{
			UE_LOG(LogTemp, Error, TEXT("Output: Cast to pollable failed in Get Pooled object"));
			return nullptr;
		}
		if(!PollableActor->IsInUse(BulletsPool[i]))
		{
			return BulletsPool[i];
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Output: No available pollable object"));
	return nullptr;
}

void UCustomGameInstance::InitPool()
{
	for(int i =0 ; i < Max_Pool_Size ; i++)
	{
		auto Bullet = GetWorld()->SpawnActor<AActor>(BulletObjectClass, FVector(0,0,0),FRotator(0,0,0));
		//cast bullet to Pollable Interface
		auto Pollable = Cast<IPollable>(Bullet);
		if (Pollable)
		{
			Pollable->Deactivate();
		}
		BulletsPool.Add(Bullet);
	}
}
