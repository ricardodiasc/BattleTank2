// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK2_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere , Category=Setup)
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 40.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 0.0f;

	
	
};
