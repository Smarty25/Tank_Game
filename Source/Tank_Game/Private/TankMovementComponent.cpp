// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (abs(GetOwner()->GetVelocity().X) < MaxXVelocity && abs(GetOwner()->GetVelocity().Y) < MaxYVelocity && abs(GetOwner()->GetVelocity().Z) < MaxZVelocity)
	{
		Throw = FMath::Clamp(Throw, -1.f, 1.f);
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	Throw = FMath::Clamp(Throw, -1.f, 1.f);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIIntention = MoveVelocity.GetSafeNormal();

	float AIForwardThrow = FVector::DotProduct(TankForward, AIIntention);
	IntendMoveForward(AIForwardThrow * AIMovementScaleFactor);

	float AITurningThrow = FVector::CrossProduct(TankForward, AIIntention).Z;
	IntendTurnRight(AITurningThrow * AIMovementScaleFactor);
}
