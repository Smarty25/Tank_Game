// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANK_GAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	APawn * Player = nullptr;

	ATank * PossessedTank = nullptr;

	UTankAimingComponent * AimingComponent = nullptr;

	float AcceptanceRadius = 5000;

	virtual void SetPawn(APawn * InPawn) override;

	UFUNCTION()
	void OnTankDeath();
};
