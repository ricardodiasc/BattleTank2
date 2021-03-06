// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//~ Forward Declaration
class ATank;
class UTankAimingComponent;

/**
 * Responsible for implement player controller
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

	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();
	
	//---------------DO NOT IMPLEMENT THIS IN C++ -----------------------------
	//Event Responsible for trigger TankAimingComponent Found. It is blueprint implemented 
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimComponent(UTankAimingComponent* AimComponent);

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();
private:
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenPosition, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &Hitlocation) const ;
};
