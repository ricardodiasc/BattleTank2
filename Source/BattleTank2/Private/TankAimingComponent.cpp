// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	// Set initial LastFireTime for first fire after reloading.
	LastFireTime = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringStatus::RELOADING;
	}
	else if(IsBarrelMoving()){
		FiringState = EFiringStatus::AIMING;
	}
	else {
		FiringState = EFiringStatus::LOCKED;
	}
}


void UTankAimingComponent::Initialize(UTankBarrel* TankBarrel, UTankTurret* TankTurret) {
	this->Barrel = TankBarrel;
	this->Turret = TankTurret;

}

void UTankAimingComponent::AimAt(FVector HitLocation) {
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
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (ensure(Barrel != nullptr)) {
		auto BarrelForwardVector = Barrel->GetForwardVector();
		if (!BarrelForwardVector.Equals(AimDirection,0.01f)) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void UTankAimingComponent::Fire() {

	//bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	
	if (ensure(Barrel != nullptr)) {
		if(ensure(ProjectileBlueprint != nullptr)) {
			if (FiringState != EFiringStatus::RELOADING) {
				auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
				auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
				FActorSpawnParameters SpawnParameters;
				auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation, SpawnParameters);

				Projectile->LaunchProjectile(LaunchSpeed);

				LastFireTime = FPlatformTime::Seconds();
			}
		}
	}

}