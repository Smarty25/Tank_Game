// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	FTankDelegate OnDeath;
	CurrentHealth = MaxHealth;
	/*TakeDamage(10, FDamageEvent::FDamageEvent(), UGameplayStatics::GetPlayerController(GetWorld(), 0), Cast<AActor>(this));*/
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0.f, CurrentHealth);
	CurrentHealth = CurrentHealth - DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHealth)
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth/MaxHealth;
}
