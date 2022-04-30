// Fill out your copyright notice in the Description page of Project Settings.

#include "AIShooterCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleShooter/Actors/GunBase.h"
#include "SimpleShooter/Controllers/ShooterAIController.h"

AAIShooterCharacter::AAIShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AAIShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<UCapsuleComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AAIShooterCharacter::OnOverlapBegin);
	Cast<UCapsuleComponent>(RootComponent)->OnComponentEndOverlap.AddDynamic(this, &AAIShooterCharacter::OnOverlapEnd);
}

void AAIShooterCharacter::TakeCover()
{
	FHitResult WallTraceHit;
	if(bIsTakingCover)
	{
		StopCover();
		bIsTakingCover = false;
	}
	else if (bIsOverlappingWithCover)
	{
		StartCover(WallTraceHit.Normal);
		bIsTakingCover = true;
	}
}

void AAIShooterCharacter::SetMovementSpeed(float Speed)
{
	MovementComponent->MaxWalkSpeed = Speed;
}

void AAIShooterCharacter::Shoot()
{
	if(!bIsReloading && !bIsHit)
	{
		if(bIsTakingCover && !bIsAiming) return;
		AController* OwnerCtrl = GetController();
		if(OwnerCtrl == nullptr) return;
		
		FVector ViewportLoc;
		FRotator ViewportRot;
		OwnerCtrl-> GetPlayerViewPoint( ViewportLoc, ViewportRot);
		ViewportRot.Add(2.0,0,0);
		Gun->PullTrigger(ViewportLoc, ViewportRot.Vector());
		FOnFireWeapon.Broadcast(this);
		RemainingBullets--;
	}
}

void AAIShooterCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("CoverSpot"))
	{
		bIsOverlappingWithCover = true;
		OnOverlapWithCover.Broadcast(OtherActor);
	}
}

void AAIShooterCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsOverlappingWithCover = false;
}

void AAIShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


