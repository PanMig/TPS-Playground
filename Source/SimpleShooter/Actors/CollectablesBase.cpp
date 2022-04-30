// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectablesBase.h"
#include "Components/BoxComponent.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

// Sets default values
ACollectablesBase::ACollectablesBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh -> SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACollectablesBase::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACollectablesBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectablesBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACollectablesBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
}

