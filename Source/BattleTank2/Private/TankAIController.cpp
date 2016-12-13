// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "Tank.h"
#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//TODO: move towards player
	//TODO: aim
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
	//TODO: fire
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (!PlayerController) {
		UE_LOG(LogTemp, Error, TEXT("AI Tank not found PLayer Controller"));
		return nullptr; 
	}
	ATank* PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	
	return PlayerTank;
}


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No AI tank possesssed for player..."));
	}
	else {
		auto Name = ControlledTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AI possesed by :%s"), *Name);
		auto PlayerTank = GetPlayerTank();
		auto PlayerTankName = PlayerTank->GetName();

		UE_LOG(LogTemp, Warning, TEXT("AI Got Player Controller with name %s"), *PlayerTankName);
	}
}