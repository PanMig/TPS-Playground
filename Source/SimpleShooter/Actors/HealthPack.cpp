// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/BoxComponent.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

void AHealthPack::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AHealthPack::OnOverlapEnd);
}

void AHealthPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,TEXT("Entered"));
	AShooterCharacter* OtherShooter = Cast<AShooterCharacter>(OtherActor);
	if(OtherShooter != nullptr)
	{
		OtherShooter->CollectHealthPack(HealthIncrease);
		Destroy();
	}
}

void AHealthPack::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,TEXT("Exited"));
}
