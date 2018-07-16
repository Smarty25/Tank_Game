// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankMovementComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	Player = (GetWorld()->GetFirstPlayerController()->GetPawn());
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToActor(Player, AcceptanceRadius);

	if (ensure(AimingComponent))
	{
		AimingComponent->Aim(Player->GetActorLocation());
	}

	if (AimingComponent->IsLocked())
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	PossessedTank->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("AI TANK DIED"))
}
