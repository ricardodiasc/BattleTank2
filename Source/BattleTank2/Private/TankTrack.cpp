// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankTrack.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle) {
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttling at %f"), *Name, Throttle);

	auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce * Throttle;

	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("I`m hit!!!"));
}

void UTankTrack::TickComponent(float DeltaTime,enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Calculate Slippage Speed
		//How fast tank track is going right
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Vector to opposing direction of slippage
	FVector CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());
	

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto TankMass = TankRoot->GetMass();

	auto CorrectionForce = (TankMass * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce);

	//Work out required acceleration to correct in this frame
	//Calculat eand apply sideways force for (F = m * a)
}

