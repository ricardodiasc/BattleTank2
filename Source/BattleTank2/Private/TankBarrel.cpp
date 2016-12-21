// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f , 1.0f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	float NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	//FMath::Clamp()
	SetRelativeRotation(FRotator(NewElevation, 0.0f, 0.0f));
}

