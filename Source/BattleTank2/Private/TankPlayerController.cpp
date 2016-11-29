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
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location is %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {
	

	//Find cross hair projection
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	float PosX = ViewportSizeX * CrossHairLocationX;
	float PosY = ViewportSizeY * CrossHairLocationY;
	FVector2D ScreenPosition = FVector2D(PosX, PosY);

	//UE_LOG(LogTemp, Warning, TEXT("PosX : %f - PosY: %f"), PosX, PosY);

	FVector LookDirection;
	if (GetLookDirection(ScreenPosition, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("World Direction %s"), *LookDirection.ToString());
		return GetLookVectorHitLocation(LookDirection, HitLocation);
		//return true;
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenPosition, FVector &LookDirection) const {
	FVector WorldLocation; // Camera position. To be discarded.
	return DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FCollisionQueryParams Params;
	FCollisionResponseParams ResponseParams;
	bool LineTraceResult = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, Params, ResponseParams);
	if (LineTraceResult) {
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		HitLocation = FVector::ZeroVector;
		return false;
	}
}