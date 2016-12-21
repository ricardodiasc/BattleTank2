// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank2.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimComponent != nullptr)) {
		FoundAimComponent(AimComponent);
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
	//Test GetPawn() in case there is nothing possessing that tank.
	// For some reason, the editor crash in here if no test and exit
	if (!GetPawn()) { return; }
	
	auto AimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimComponent)) {
		FVector HitLocation;

		if (GetSightRayHitLocation(HitLocation)) {
			AimComponent->AimAt(HitLocation);
		}
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {
	

	//Find cross hair projection
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	float PosX = ViewportSizeX * CrossHairLocationX;
	float PosY = ViewportSizeY * CrossHairLocationY;
	FVector2D ScreenPosition = FVector2D(PosX, PosY);

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