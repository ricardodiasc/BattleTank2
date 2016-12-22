// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK2_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 8000.0f;
public:
	ATankAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//Distance to AI tank can approximate

};
