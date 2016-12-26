// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"


ATankAIController::ATankAIController() {
	PrimaryActorTick.bCanEverTick = true;

}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	
	
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (ensure(PlayerTank != nullptr) && ensure(ControlledTank != nullptr)) {
		MoveToActor(PlayerTank, AcceptanceRadius);
		auto AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		AimComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimComponent->GetFiringState() == EFiringStatus::LOCKED) {
			AimComponent->Fire();
		}
	}
}

void ATankAIController::OnTankDeath()
{
	auto TankPawn = GetPawn();
	if (TankPawn != nullptr) {
		TankPawn->DetachFromControllerPendingDestroy();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn != nullptr) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (ensure(PossessedTank != nullptr)) {
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
		}
	}

}



