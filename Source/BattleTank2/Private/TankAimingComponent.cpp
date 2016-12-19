// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::Initialize(UTankBarrel* TankBarrel, UTankTurret* TankTurret) {
	this->Barrel = TankBarrel;
	this->Turret = TankTurret;

}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (ensure(Barrel != nullptr)) {
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam,
			TArray<AActor*>(),
			false);

		if (bHaveAimSolution) {
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

			MoveBarrelTowards(AimDirection);
		
		}
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	if (!ensure(BarrelToSet)) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	this->Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}