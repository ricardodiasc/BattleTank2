// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK2_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATankAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//Distance to AI tank can aproximate
	float AcceptanceRadius = 3000.0f;
};
