// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus :uint8 {
	RELOADING,
	AIMING,
	LOCKED
};


class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK2_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();


	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrel(UTankBarrel* BarrelToSet);
	void SetTurret(UTankTurret* TurretToSet);

	UPROPERTY(BlueprintReadOnly, Category="Firing State")
	EFiringStatus FiringState = EFiringStatus::LOCKED;
private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;


	//Move Barrel towards to a aim direction
	void MoveBarrelTowards(FVector AimDirection);
	
};
