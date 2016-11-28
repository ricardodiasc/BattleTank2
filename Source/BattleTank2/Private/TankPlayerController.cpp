// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank2.h"
#include "Tank.h"
#include "TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("No tank possesssed for player..."));
	}
	else {
		auto Name = ControlledTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Player possesed by :%s"), *Name);
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AimTowardsCrosshair();

}

//Aim At Crosshair on screen. Used as reference to rotate the barrel.
void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Location is %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) {
	HitLocation = FVector(1.0f);
	return true;
}