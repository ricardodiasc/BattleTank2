// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttling at %f"), *Name, Throttle);

	auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce * Throttle;

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

