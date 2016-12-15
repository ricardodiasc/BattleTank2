// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;

/**
 * Manage Tank movement
 */
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup =(Custom))
class BATTLETANK2_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	//Initialize Tank Movement Component setting Tank tracks
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* TankLeftTrack, UTankTrack* TankRightTrack);
	
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);
private:
	UTankTrack* TankLeftTrack = nullptr;
	UTankTrack* TankRightTrack = nullptr;
};
