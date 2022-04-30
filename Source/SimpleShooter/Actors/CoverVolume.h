// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "CoverVolume.generated.h"

UCLASS()
class SIMPLESHOOTER_API ACoverVolume : public AActor
{
	GENERATED_BODY()
private:
	bool bIsCoverOccupied;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* CoverSpot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SM;
	
	ACoverVolume();
	
	virtual void Tick(float DeltaTime) override;

	bool IsOccupied() const;
	void SetIsOccupied(bool Status);
	FVector GetCoverSpotLocation() const;
};
