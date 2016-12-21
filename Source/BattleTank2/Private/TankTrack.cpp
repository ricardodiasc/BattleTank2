// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f,1.0f);	
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce * CurrentThrottle;

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}


void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());


	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto TankMass = TankRoot->GetMass();

	auto CorrectionForce = (TankMass * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce);
}

