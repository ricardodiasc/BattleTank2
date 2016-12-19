// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
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

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (ensure(PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}



