// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectablesBase.generated.h"
class UBoxComponent;

UCLASS()
class SIMPLESHOOTER_API ACollectablesBase : public AActor
{
	GENERATED_BODY()
	

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Box Collider")
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, Category="Base Mesh")
	UStaticMeshComponent* BaseMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
    virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	
	ACollectablesBase();
	
	virtual void Tick(float DeltaTime) override;	
};
