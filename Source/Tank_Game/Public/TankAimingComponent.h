// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EReloadStatus : uint8 {Reloaded, Reloading};

class UTankBarrel;
class UTankTurret;
class UGameplayStatics;
class UStaticMeshComponent;
class UActorComponent;
class UWorld;
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_GAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankTurret * TankTurretToSet, UTankBarrel * TankBarrelToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Aim(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	bool IsLocked();

	FVector GetAimDirection(FVector BarrelLocation, FVector HitLocation, float LaunchSpeed, bool & bSuccess);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	EReloadStatus ReloadStatus = EReloadStatus::Reloaded;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> Projectile_BP;

	void MoveBarrel(FRotator BarrelDirection);

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadSpeed = 3;

	double LastFireTime = FPlatformTime::Seconds() - ReloadSpeed;

	bool bIsReloaded = true;

	FVector AimDirection;
};