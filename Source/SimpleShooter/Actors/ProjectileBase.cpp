// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}
	
	if(!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	ProjectileMeshComponent->SetupAttachment(RootComponent);
	
	if(!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::FireInDirection(const FRotator& ShootDirection, float RotationOffset, const FVector& RotationAxis)
{
	auto dir = ShootDirection.Vector().RotateAngleAxis(-RotationOffset,RotationAxis);
	ProjectileMovementComponent->Velocity = dir * ProjectileSpeed;
}

void AProjectileBase::FireInDirection(const FRotator& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection.Vector() * ProjectileSpeed;
}

void AProjectileBase::SetTransformation(const FVector& Position, const FRotator& Rotation)
{
	SetActorLocation(Position);
	SetActorRotation(Rotation);
}

void AProjectileBase::Activate()
{
	//UE_LOG(LogTemp, Warning, TEXT("Output: Activated"));
	bIsInUse = true;	

	TSet<UActorComponent*> Components = GetComponents();
	for (UActorComponent* ActorComponent : Components)
	{           
		ActorComponent->Activate(true);
	}

	//SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
}

void AProjectileBase::Deactivate()
{
	//UE_LOG(LogTemp, Warning, TEXT("Output: Deactivated"));
	bIsInUse = false;
	//SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
	
	TSet<UActorComponent*> Components = GetComponents();
	for (UActorComponent* ActorComponent : Components)
	{       
		ActorComponent->Deactivate();
	}
}

bool AProjectileBase::IsInUse(const AActor* PollableActor)
{
	return bIsInUse;
}

