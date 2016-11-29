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
	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;

	virtual void Tick(float DeltaSeconds) override;

private:
	ATank* GetPlayerTank() const;
	
};
