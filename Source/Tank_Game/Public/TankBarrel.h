// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankBarrel.generated.h"

class UStaticMeshComponent;
class UWorld;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_GAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 45;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0;
};
