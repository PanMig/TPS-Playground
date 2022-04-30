// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "EngineUtils.h"
#include "ProjectileBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleShooter/CustomGameInstance.h"
#include "SimpleShooter/Pollable.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Mesh -> SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunBase::PullTrigger(const FVector& ViewLocation, const FVector& ViewDirection)
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	FActorSpawnParameters SpawnParams;
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;

	AController* OwnerCtrl = OwnerPawn->GetController();
	if(OwnerCtrl == nullptr) return;
	
	FHitResult HitResult;
	FVector EndPoint = ViewLocation + ViewDirection * MaxRange;

	FCollisionQueryParams Params(NAME_None, true, OwnerPawn);
	bool bSuccess = GetWorld()-> LineTraceSingleByChannel(HitResult,ViewLocation, EndPoint, ECC_GameTraceChannel1, Params);
	//DrawDebugLine(GetWorld(),ViewLocation + 10*GetActorForwardVector(), EndPoint,FColor::Red,false,2.0f);

	//Grab a a bullet from the pool and place it in the tip of the gun (socket)
	auto GameInst = Cast<UCustomGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto PooledObj = GameInst->GetPooledObject();
	if(PooledObj)
	{
		auto BulletTrail =  Cast<AProjectileBase>(PooledObj);
		Cast<IPollable>(BulletTrail)->Activate();
		auto StartLocation = Mesh->GetSocketLocation(TEXT("MuzzleFlashSocket"));
		FRotator LookRotation;
		LookRotation = bSuccess ?
			UKismetMathLibrary::FindLookAtRotation(StartLocation,HitResult.ImpactPoint)
			: UKismetMathLibrary::FindLookAtRotation(StartLocation,HitResult.TraceEnd);
		BulletTrail->SetActorLocation(StartLocation);
		BulletTrail->FireInDirection(LookRotation);
	}
	
	
	if(bSuccess)
	{
		FVector ShotDirection = -ViewDirection; // we get the opposite since this is the direction the bullet is coming from.
		//DrawDebugPoint(GetWorld(), HitResult.Location, 10, FColor::Red,true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, HitResult.Location);
		
		//Send damage
		AActor* DamageReceiver = HitResult.GetActor();
		
		if(DamageReceiver != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			DamageReceiver -> TakeDamage(Damage, DamageEvent, OwnerCtrl,this);
			//Broadcast Bullet Hit delegate
			auto ReceiverShooterChar = Cast<AShooterCharacter>(DamageReceiver);
			if(ReceiverShooterChar)
			{
				ReceiverShooterChar->OnTakeDmg.Broadcast(DamageReceiver,this, HitResult);
			}
		}
	}
}

