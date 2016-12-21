// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track	
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (Custom))
class BATTLETANK2_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UTankTrack();

	float CurrentThrottle = 0.0f;

	//Set force to tank track
	UFUNCTION(BlueprintCallable, Category="Tank input")
	void SetThrottle(float Throttle);

	void DriveTrack();
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0f;

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	
};
