// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SimpleShooter/Pollable.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SIMPLESHOOTER_API AProjectileBase : public AActor , public IPollable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
	
	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category=Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;

	// Projectile material
	UPROPERTY(EditAnywhere, Category = Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Projectile Velocity
	UPROPERTY(EditAnywhere)
	float ProjectileSpeed;
	
	// Function that initializes the projectile's velocity in the shoot direction.
	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FRotator& ShootDirection, float RotationOffset, const FVector& RotationAxis);

	void FireInDirection(const FRotator& ShootDirection);

	// IPollable implementations
	UPROPERTY(EditAnywhere)
	bool bIsInUse;
	UFUNCTION(BlueprintCallable, Category="Poollable")
	virtual void SetTransformation(const FVector& Position, const FRotator& Rotation) override;
	UFUNCTION(BlueprintCallable, Category="Poollable")
	virtual void Activate() override;
	UFUNCTION(BlueprintCallable, Category="Poollable")
	virtual void Deactivate() override;
	UFUNCTION(BlueprintCallable, Category="Poollable")
	virtual bool IsInUse(const AActor* PollableActor) override;

};
