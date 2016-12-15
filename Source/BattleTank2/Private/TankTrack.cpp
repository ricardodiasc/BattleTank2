// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();

	UE_LOG(LogTemp, Warning, TEXT("%s trottling at %f"), *Name, Throttle);
}

