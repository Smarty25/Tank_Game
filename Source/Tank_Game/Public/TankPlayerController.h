// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPlayerController.generated.h"

class UWorld;
class UTankAimingComponent;
class APlayerController;

/**
 * 
 */
UCLASS()
class TANK_GAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void AimAtCrosshair();
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * AimingComponent = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void AimingComponentSet();

private:
	bool GetSightRayHitLocation(FVector & OutHitLocation);

	bool GetHitLocation(FVector LookDirection, FVector & OutHitLocation);

	FVector GetLookDirection();

	UPROPERTY(EditAnywhere)
		float CrosshairX = .5;

	UPROPERTY(EditAnywhere)
		float CrosshairY = .3333;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};