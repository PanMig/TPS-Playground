// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGunBase;
class UCapsuleComponent;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTakeDmg, AActor*, Receiver, AActor*, Causer, const FHitResult&, ImpactHit);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFireWeapon, AActor*, Causer);

private:
	// Character Movement
	void MoveForward(float AxisValue);
	void Strafe(float AxisValue);
	
	//Used for frame ate independent controller Input
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float RotationRate = 100;

	UPROPERTY(EditDefaultsOnly, Category="Gun")
	TSubclassOf<AGunBase> GunClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gun")
	AGunBase* Gun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 1000;
	
	UPROPERTY()
	float Health;

	bool bIsCrouching;
	bool bIsProne;
	bool bIsShooting;
	bool bIsTakingCover;
	bool bIsAiming;
	bool bIsReloading;
	float CoverRightMovementDir;

	UCharacterMovementComponent* MovementComponent;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
		AActor* DamageCauser) override;
	
public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Actions
	UFUNCTION(BlueprintCallable)
	virtual void Shoot();
	UFUNCTION(BlueprintCallable)
	void CrouchAction();
	UFUNCTION(BlueprintCallable)
	virtual void TakeCover();
	UFUNCTION(BlueprintCallable)
	void ProneAction();
	UFUNCTION(BlueprintCallable)
	void AimToggleAction();
	UFUNCTION(BlueprintCallable)
	void Reload();

	//Cover action handling
	bool CanGetToCover(FHitResult& HitResult);
	void StartCover(FVector AxisDirection);
	void StopCover();
	UFUNCTION(BlueprintCallable)
	void EnterCrouch();
	UFUNCTION(BlueprintCallable)
	void ExitCrouch();

	//Getters Setters
	UFUNCTION(BlueprintPure)
	float GetCoverMovementDir();
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	bool IsProne() const;

	UFUNCTION(BlueprintPure)
	bool IsCrouching() const;
	
	UFUNCTION(BlueprintPure)
    bool IsCovering() const;

	UFUNCTION(BlueprintCallable)
	bool GetIsAiming() const;
	
	UFUNCTION(BlueprintCallable)
    float GetHealth() const;

	UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetIsReloading() const;

    void CollectHealthPack(float HealthIncrease);

	UFUNCTION(BlueprintPure)
    float GetStartingHealth() const;

	UFUNCTION(BlueprintPure)
	void OnGetHit(AActor* Receiver, AActor* Causer, const FHitResult& ImpactHit);

	// Properties
	UPROPERTY(BlueprintAssignable)
	FOnTakeDmg OnTakeDmg;

	UPROPERTY(BlueprintAssignable)
	FOnFireWeapon FOnFireWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHit = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BulletHitAngle = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RemainingBullets;

	//inline
	UFUNCTION(BlueprintCallable)
	inline void SetIsAiming(bool status){ bIsAiming = status;}

	bool GetIsHit() const {return bIsHit;}
};
