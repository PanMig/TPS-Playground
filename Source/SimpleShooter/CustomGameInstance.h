// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<AActor*> BulletsPool;

	UPROPERTY(EditAnywhere)
	int32 Max_Pool_Size;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectileBase> BulletObjectClass;
public:
	virtual void OnStart() override;
	AActor* GetPooledObject();
	void InitPool();
};
