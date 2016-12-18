// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* TankLeftTrack, UTankTrack* TankRightTrack) {
	if (!ensure(TankLeftTrack && TankRightTrack)) { return; }
	
	this->TankLeftTrack = TankLeftTrack;
	this->TankRightTrack = TankRightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!ensure(TankLeftTrack && TankRightTrack)) { return; }
	TankLeftTrack->SetThrottle(Throw);
	TankRightTrack->SetThrottle(Throw);

	//TODO Prevent double speed on dual control use
}

void UTankMovementComponent::IntendMoveRight(float Throw) {
	if (ensure(TankLeftTrack != nullptr && TankRightTrack != nullptr)) { 
		TankLeftTrack->SetThrottle(Throw);
		TankRightTrack->SetThrottle(-Throw);
	}

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//No need to call Super because we are replacing the functionality
	
	//auto TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Tank AI [%s] is headed towards to %s"),*TankName, *MoveVelocity.ToString())
	
	auto TankForwardVector = GetOwner()->GetActorForwardVector().SafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float AIThrow = FVector::DotProduct(TankForwardVector, AIForwardIntention);
	
	auto  RightThrow = FVector::CrossProduct(TankForwardVector, AIForwardIntention).Z;
	IntendMoveRight(RightThrow);
	IntendMoveForward(AIThrow);
}