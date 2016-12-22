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
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK2_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFireTime = 0.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint;


	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

	void AimAt(FVector HitLocation);


	UFUNCTION(BlueprintCallable, Category = "Custom")
	void Fire();


	EFiringStatus GetFiringState();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Firing State")
	EFiringStatus FiringState = EFiringStatus::RELOADING;
private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;

	

	FVector AimDirection;


	//Move Barrel towards to a aim direction
	void MoveBarrelTowards(FVector AimDirection);

	//Checks if barrel is moving to guide aim Crosshair
	bool IsBarrelMoving();
	
};
