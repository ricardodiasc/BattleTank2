// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank2.h"
#include "TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto PossessedTank = GetControlledTank();
	if (!PossessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank possesssed for player..."));
	}
	else {
		auto Name = PossessedTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Player possesed by :%s"), *Name);
	}
}