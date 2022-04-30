// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISightTargetInterface.h"
#include "PlayerShooterCharacter.generated.h"
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API APlayerShooterCharacter : public AShooterCharacter, public IGenericTeamAgentInterface , public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	APlayerShooterCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable)
	void DrawProjectilePath();
	UFUNCTION(BlueprintCallable)
	void FindTeleportDestination(TArray<FVector> &OutPath, FVector &OutLocation);
	UFUNCTION(BlueprintCallable)
	void ConstructProjectilePath(const TArray<FVector> &Path);
	UFUNCTION(BlueprintCallable)
	void ClearProjectilePath();
	void UpdateSpline(const TArray<FVector> &Path);
	//Niagra based projectile trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* ProjectileArc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TeleportLookOffset;
private:
	FGenericTeamId TeamId;
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	UPROPERTY(VisibleDefaultsOnly, Category= "AI perception Stimuli")
	UAIPerceptionStimuliSourceComponent* AIStimuli;

	UFUNCTION(BlueprintCallable)
	void DrawProjectileArc(TArray<FPredictProjectilePathPointData>& PathData);
	
	UPROPERTY(VisibleAnywhere)
	class USplineComponent* ProjectileTracePath;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

	UPROPERTY()
	TArray<class UStaticMeshComponent*> ProjectileTracePathMeshPool;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMesh* ProjectilePathArchMesh;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* ProjectilePathArchMaterial;

	UPROPERTY(EditAnywhere)
	float TeleportProjectileRadius = 10;

	UPROPERTY(EditAnywhere)
	float TeleportProjectileSpeed = 800;

	UPROPERTY(EditAnywhere)
	float ProjectileLookRotationOffset = 20.0f;
	
	UPROPERTY(EditAnywhere)
	FVector TeleportProjectionExtent = FVector(100, 100, 100);

	UPROPERTY(EditAnywhere)
	float TeleportSimulationTime;

	virtual bool CanBeSeenFrom(const FVector& ObserverLocation,
		FVector& OutSeenLocation,
		int32& NumberOfLoSChecksPerformed,
		float& OutSightStrength,
		const AActor* IgnoreActor = nullptr,
		const bool* bWasVisible = nullptr,
		int32* UserData = nullptr) const;
};
