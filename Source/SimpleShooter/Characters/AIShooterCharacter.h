// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterCharacter.h"
#include "Perception/AISightTargetInterface.h"
#include "AIShooterCharacter.generated.h"

class AShooterAIController;
class UWidgetComponent;
class UPawnSensingComponent;
class AShooterCharacter;


UCLASS()
class SIMPLESHOOTER_API AAIShooterCharacter : public AShooterCharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlapWithCover, AActor*, Other);

private:
	AShooterAIController* AICtrl;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsOverlappingWithCover = false;

public:
	AAIShooterCharacter();

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category="Patrol Points", BlueprintReadWrite)
	TArray<AActor*> PatrolPoints;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float JogSpeed;

	UPROPERTY(EditAnywhere)
	class ATriggerVolume* CombatZoneVolume;
	
	virtual void TakeCover() override;

	void SetMovementSpeed(float Speed);

	virtual void Shoot() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(BlueprintAssignable)
	FOnOverlapWithCover OnOverlapWithCover;

	ATriggerVolume* GetCombatZoneVolume() const
	{
		return CombatZoneVolume;
	}
};
