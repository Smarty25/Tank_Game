// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	AimingComponentSet();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	/*OUT*/ FVector HitLocation;
	if (GetSightRayHitLocation(/*OUT*/HitLocation) && ensure(AimingComponent))
	{
		AimingComponent->Aim(HitLocation);
	}
	return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & /*OUT*/OutHitLocation)
{
	FVector LookDirection = GetLookDirection();
	return GetHitLocation(LookDirection, /*OUT*/OutHitLocation);
}

bool ATankPlayerController::GetHitLocation(FVector LookDirection, FVector & /*OUT*/OutHitLocation)
{
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (LookDirection * LineTraceRange);
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel
	(
		/*OUT*/HitResult,
		Start,
		End,
		ECC_Visibility
	))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}

FVector ATankPlayerController::GetLookDirection()
{
	int32 ViewportX, ViewPortY;
	GetViewportSize(/*OUT*/ViewportX, /*OUT*/ViewPortY);
	FVector2D ScreenLocation = FVector2D(ViewportX * CrosshairX, ViewPortY * CrosshairY);
	FVector WorldLocation;
	FVector WorldDirection;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, /*OUT*/WorldLocation, /*OUT*/WorldDirection);
	return WorldDirection;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank * PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	Cast<APlayerController>(this)->StartSpectatingOnly();
	UE_LOG(LogTemp, Warning, TEXT("Player TANK DIED"))
}
