// Fill out your copyright notice in the Description page of Project Settings.


#include "CoverVolume.h"


// Sets default values
ACoverVolume::ACoverVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = SM;
		
	CoverSpot = CreateDefaultSubobject<USceneComponent>("CoverSpot");
	CoverSpot->SetupAttachment(RootComponent);

	BoxVolume = CreateDefaultSubobject<UBoxComponent>("BoxVolume");
	BoxVolume->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACoverVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoverVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ACoverVolume::IsOccupied() const
{
	return  bIsCoverOccupied;
}

void ACoverVolume::SetIsOccupied(bool Status)
{
	bIsCoverOccupied = Status;
}

FVector ACoverVolume::GetCoverSpotLocation() const
{
	return CoverSpot->GetComponentLocation();
}

