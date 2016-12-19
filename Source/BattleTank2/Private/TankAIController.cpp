// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankAimingComponent.h"
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
		AimComponent->Fire();
	}
}



