// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* TankLeftTrack, UTankTrack* TankRightTrack) {
	if (!TankLeftTrack || !TankRightTrack) { return; }
	
	this->TankLeftTrack = TankLeftTrack;
	this->TankRightTrack = TankRightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("Throw at %f"), Throw);
	if (!TankLeftTrack || !TankRightTrack) { return; }

	TankLeftTrack->SetThrottle(Throw);
	TankRightTrack->SetThrottle(Throw);

	//TODO Prevent double speed on dual control use
}