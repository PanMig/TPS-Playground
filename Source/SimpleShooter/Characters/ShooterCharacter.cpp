// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Chaos/ChaosDebugDraw.h"
#include "SimpleShooter/Actors/GunBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AShooterCharacter::IsDead() const
{
	if(Health > 0) {return false;}
	return true;
}

bool AShooterCharacter::IsProne() const
{
	return bIsProne;
}

bool AShooterCharacter::IsCrouching() const
{
	return bIsCrouching;
}

bool AShooterCharacter::IsCovering() const
{
	return bIsTakingCover;
}

bool AShooterCharacter::GetIsAiming() const
{
	return bIsAiming;
}

float AShooterCharacter::GetHealth() const
{
	return Health;
}

float AShooterCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

float AShooterCharacter::GetIsReloading() const
{
	return bIsReloading;
}

void AShooterCharacter::CollectHealthPack(float HealthIncrease)
{
	if(Health < MaxHealth)
	{
		Health += HealthIncrease;
	}

	UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);
}

float AShooterCharacter::GetStartingHealth() const
{
	return MaxHealth;
}

void AShooterCharacter::OnGetHit(AActor* DamageReceiver, AActor* DamageCauser, const FHitResult& ImpactPoint)
{
	const FVector DamagedActorFront = DamageReceiver-> GetActorForwardVector();
	const FVector DamageReceiverFront = ImpactPoint.ImpactNormal;
	BulletHitAngle = UKismetMathLibrary::DegAcos(FVector::DotProduct(DamagedActorFront, DamageReceiverFront));
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Spawn Gun Object and attack to socket.
	Gun = GetWorld()-> SpawnActor<AGunBase>(GunClass);
	GetMesh()-> HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun -> AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun-> SetOwner(this);

	//Set Actor health
	Health = MaxHealth;

	//Bind BulletHit Delegate
	OnTakeDmg.AddDynamic(this, &AShooterCharacter::OnGetHit);

	//Grab MovementComponent
	MovementComponent = FindComponentByClass<UCharacterMovementComponent>();
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CoverRightMovementDir = GetInputAxisValue("MoveRight");
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &AShooterCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Shoot"),IE_Pressed,this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Crouch"),IE_Pressed,this, &AShooterCharacter::CrouchAction);
	PlayerInputComponent->BindAction(TEXT("TakeCover"),IE_Pressed,this, &AShooterCharacter::TakeCover);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this, &ACharacter::Jump);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	if(!bIsProne)
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::Strafe(float AxisValue)
{
	if(!bIsProne)
	AddMovementInput(GetActorRightVector() * AxisValue);
}

//Used for frame ate independent controller Input
void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	if(!bIsReloading && !bIsHit)
	{
		if(bIsTakingCover && !bIsAiming) return;
		AController* OwnerCtrl = GetController();
		if(OwnerCtrl == nullptr) return;
		
		FVector ViewportLoc;
		FRotator ViewportRot;
		OwnerCtrl-> GetPlayerViewPoint( ViewportLoc, ViewportRot);
		Gun->PullTrigger(ViewportLoc, ViewportRot.Vector());
		FOnFireWeapon.Broadcast(this);
		RemainingBullets--;	
	}
}

void AShooterCharacter::CrouchAction()
{
	if(bIsCrouching)
	{
		bIsCrouching = false;
		if(MovementComponent) UnCrouch();
		return;
	}
	bIsCrouching = true;
	if(MovementComponent)
	{
		Crouch(); 
	}
}

void AShooterCharacter::TakeCover()
{
	FHitResult WallTraceHit;
	if(bIsTakingCover)
	{
		StopCover();
		bIsTakingCover = false;
		UnCrouch();
	}
	else if (CanGetToCover(WallTraceHit))
	{
		StartCover(WallTraceHit.Normal);
		Crouch();
		bIsTakingCover = true;
	}
}

void AShooterCharacter::ProneAction()
{
	if(bIsProne)
	{
		bIsProne = false;
		if(MovementComponent) UnCrouch();
		return;
	}
	bIsProne = true;
	if(MovementComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MovementComponent->GetOwner()->GetName());
		Crouch(); 
	}
}

void AShooterCharacter::AimToggleAction()
{
	bIsAiming = (bIsAiming == true) ? false : true;
	if(bIsAiming && bIsTakingCover) UnCrouch();
	else if(!bIsAiming && bIsTakingCover) Crouch();
}

void AShooterCharacter::Reload()
{
	bIsReloading = true;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{RemainingBullets = MagazineSize; bIsReloading = false;}, 2.17f, false);
}

bool AShooterCharacter::CanGetToCover(FHitResult& HitResult)
{
	FVector StarPos = GetActorLocation();
	FVector EndPos = GetActorForwardVector() * 400.0f + StarPos;
	FCollisionQueryParams Params;
	//auto result = GetWorld()->LineTraceSingleByChannel(HitResult, StarPos, EndPos, ECollisionChannel::ECC_GameTraceChannel2, Params);
	auto result = GetWorld()->LineTraceSingleByChannel(HitResult, StarPos, EndPos, ECollisionChannel::ECC_GameTraceChannel2, Params);
	//DrawDebugLine(GetWorld(),StarPos, EndPos,FColor::Red,false, 10.0f);
	return result;
}

void AShooterCharacter::StartCover(FVector AxisDirection)
{
	bIsTakingCover = true;
	MovementComponent->SetPlaneConstraintEnabled(true);
	MovementComponent->SetPlaneConstraintNormal(AxisDirection);
	bUseControllerRotationYaw = false;
}

void AShooterCharacter::StopCover()
{
	MovementComponent->SetPlaneConstraintEnabled(false);
	bUseControllerRotationYaw = true;
}

void AShooterCharacter::EnterCrouch()
{
	bIsCrouching = true;
	Crouch();
}

void AShooterCharacter::ExitCrouch()
{
	bIsCrouching = false;
	UnCrouch();
}

float AShooterCharacter::GetCoverMovementDir()
{
	return CoverRightMovementDir;
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage( DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//Reduce health by damage
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	
	if(IsDead())
	{
		// Call Pawn killed from controller before detaching.
		auto GM= GetWorld()-> GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GM != nullptr)
		{
			GM->PawnKilled(this);
		}
		
		//Detach controller
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

