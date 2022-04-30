// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooterCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Components/SplineComponent.h"
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include <NiagaraDataInterfaceArrayFunctionLibrary.h>
#include "SimpleShooter/Controllers/ShooterPlayerController.h"

APlayerShooterCharacter::APlayerShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIStimuli = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AI Stimuli"));

	ProjectileTracePath = CreateDefaultSubobject<USplineComponent>(TEXT("TeleportPath"));
	ProjectileTracePath->SetupAttachment(RootComponent);

	ProjectileArc = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileArc"));
	ProjectileArc -> SetupAttachment(GetRootComponent());

	TeamId = FGenericTeamId(0);
}

void APlayerShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerShooterCharacter::DrawProjectilePath()
{
	// TArray<FVector> Path;
	// FVector Location;
	// FindTeleportDestination(Path, Location);
	// ConstructProjectilePath(Path);
}

void APlayerShooterCharacter::FindTeleportDestination(TArray<FVector>& OutPath, FVector& OutLocation)
{
	FVector Start = GetMesh()->GetSocketLocation("WeaponSocket");
	//get cam forward vector
	auto camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = camManager->GetCameraLocation();
	FVector camForward  = camManager->GetCameraRotation().Vector();
	// rotates  vector direction by offset on negative(up)
	camForward = camForward.RotateAngleAxis(-TeleportLookOffset,GetActorRightVector());
	FVector Look = GetActorForwardVector() * camForward;

	FPredictProjectilePathParams Params(
		TeleportProjectileRadius, 
		Start,
		camForward * TeleportProjectileSpeed,
		TeleportSimulationTime,
		ECollisionChannel::ECC_Visibility,
		this
	);
	//Params.DrawDebugType = EDrawDebugTrace::ForOneFrame;
	//Params.bTraceComplex = true;
	FPredictProjectilePathResult Result;
	bool bHit = UGameplayStatics::PredictProjectilePath(this, Params, Result);

	for (FPredictProjectilePathPointData PointData : Result.PathData)
	{
		OutPath.Add(PointData.Location);
	}
}

void APlayerShooterCharacter::ConstructProjectilePath(const TArray<FVector>& Path)
{
	UpdateSpline(Path);

	for (int32 i = 0; i < Path.Num(); ++i)
	{
		if (ProjectileTracePathMeshPool.Num() <= i)
		{
			UStaticMeshComponent* DynamicMesh = NewObject<UStaticMeshComponent>(this);
			DynamicMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			DynamicMesh->SetStaticMesh(ProjectilePathArchMesh);
			DynamicMesh->SetMaterial(0, ProjectilePathArchMaterial);
			DynamicMesh->RegisterComponent();

			ProjectileTracePathMeshPool.Add(DynamicMesh);
		}

		UStaticMeshComponent* DynamicMesh = ProjectileTracePathMeshPool[i];

		DynamicMesh->SetWorldLocation(Path[i]);
	}
}

void APlayerShooterCharacter::ClearProjectilePath()
{
	ProjectileTracePath->ClearSplinePoints(false);
	ConstructProjectilePath(TArray<FVector>{});
}

void APlayerShooterCharacter::UpdateSpline(const TArray<FVector>& Path)
{
	ProjectileTracePath->ClearSplinePoints(false);

	for (int32 i = 0; i < Path.Num(); ++i)
	{
		FVector LocalPosition = ProjectileTracePath->GetComponentTransform().InverseTransformPosition(Path[i]);
		FSplinePoint Point(i, LocalPosition, ESplinePointType::Curve);
		ProjectileTracePath->AddPoint(Point, false);
	}

	ProjectileTracePath->UpdateSpline();
}

FGenericTeamId APlayerShooterCharacter::GetGenericTeamId() const
{
	return TeamId;
}

void APlayerShooterCharacter::DrawProjectileArc(TArray<FPredictProjectilePathPointData>& PathData)
{
	if (ProjectileArc == nullptr) return;

	TArray<FVector> Points;
	for (const FPredictProjectilePathPointData& Point : PathData)
	{
		Points.Add(Point.Location);
	}
}

bool APlayerShooterCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation,
	int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible,
	int32* UserData) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;
	
	auto sockets = GetMesh()->GetAllSocketNames();

	for (int i = 0; i < sockets.Num(); i++)
	{
		FVector socketLocation = GetMesh()->GetSocketLocation(sockets[i]);

		// const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, socketLocation
		// 	, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)) // << Changed this line
		// 	, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

		FCollisionQueryParams Params;
		const bool bHitSocket = GetWorld()->LineTraceSingleByChannel(HitResult, ObserverLocation, socketLocation,ECC_Visibility, Params);

		NumberOfLoSChecksPerformed++;

		if (bHitSocket == false || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this))) {
			OutSeenLocation = socketLocation;
			OutSightStrength = 1;
			// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White,FString::Printf(
			// 	                                 TEXT("Seen: %s"), *sockets[i].ToString()));
			return true;
		}
	}

	const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation()
		, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)) // << Changed this line
		, FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

	NumberOfLoSChecksPerformed++;

	if (bHit == false || (IsValid(HitResult.GetActor()) && HitResult.GetActor()->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;

		return true;
	}

	OutSightStrength = 0;
	return false;
}


