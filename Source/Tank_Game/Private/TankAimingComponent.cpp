// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::Initialize(UTankTurret * TankTurretToSet, UTankBarrel * TankBarrelToSet)
{
	Turret = TankTurretToSet;
	Barrel = TankBarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadSpeed;

	if (bIsReloaded)
	{
		ReloadStatus = EReloadStatus::Reloaded;
	}
	else
	{
		ReloadStatus = EReloadStatus::Reloading;
	}
}

void UTankAimingComponent::Aim(FVector HitLocation)
{
	FVector BarrelLocation = Turret->GetComponentLocation();// GetSocketLocation(FName("Projectile"));
	bool bSuccess = false;
	AimDirection = GetAimDirection(BarrelLocation, HitLocation, LaunchSpeed, /*OUT*/bSuccess);
	MoveBarrel(AimDirection.Rotation());
}

FVector UTankAimingComponent::GetAimDirection(FVector BarrelLocation, FVector HitLocation, float LaunchSpeed, bool & bSuccess)
{
	if (!Barrel) { return FVector(-10); }
	/*OUT*/FVector LaunchVelocity = FVector(0);
	TArray<AActor*> ActorsToIgnore;
	bSuccess = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		/*OUT*/LaunchVelocity,
		BarrelLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams(),
		ActorsToIgnore,
		false
	);
	return LaunchVelocity.GetSafeNormal();
}

void UTankAimingComponent::MoveBarrel(FRotator AimDirection)
{
	float RelativeBarrelRotation = AimDirection.Pitch - Barrel->GetForwardVector().Rotation().Pitch;
	Barrel->Elevate(RelativeBarrelRotation);
	float RelativeTurretRotation = AimDirection.Yaw - Turret->GetForwardVector().Rotation().Yaw;
	if (abs(RelativeTurretRotation) > 180)
	{
		Turret->Rotate(-RelativeTurretRotation);
	}
	else
	{
		Turret->Rotate(RelativeTurretRotation);
	}
}

void UTankAimingComponent::Fire()
{
	if (Barrel && bIsReloaded && Projectile_BP)
	{
		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		bIsReloaded = false;
	}
}

bool UTankAimingComponent::IsLocked()
{
	if (Barrel->GetForwardVector().Equals(AimDirection, .01)) { return true; }
	return false;
}
