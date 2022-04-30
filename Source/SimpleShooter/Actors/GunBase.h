// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

#include "GunBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunBase : public AActor
{
	GENERATED_BODY()

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTakeDmg, AActor*, Receiver, AActor*, Causer, const FHitResult&, ImpactHit);
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* BulletImpact;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BulletClass;

	UPROPERTY()
	TArray<class AActor*> BulletActorPool;
	
	UPROPERTY(EditAnywhere)
	float MaxRange = 5000;

	UPROPERTY(EditAnywhere)
	float Damage = 100;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AGunBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger(const FVector& ViewLocation, const FVector& ViewDirection);
};
