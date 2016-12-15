// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//Screen Location CrossHair at LocationX
	UPROPERTY(EditDefaultsOnly)
	float CrossHairLocationX = 0.5f;
	
	//Screen Location CrossHair at Location y
	UPROPERTY(EditDefaultsOnly)
	float CrossHairLocationY = 0.333333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;


	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

private:
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenPosition, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &Hitlocation) const ;
};
