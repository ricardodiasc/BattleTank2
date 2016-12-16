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

	//Set force to tank track
	UFUNCTION(BlueprintCallable, Category="Tank input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0f;

	
};
