// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank2.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}


void ATank::AimAt(FVector HitLocation) 
{
	if (ensure(TankAimingComponent != nullptr)) { 
		TankAimingComponent->AimAt(HitLocation, LauchSpeed);
	}
}

void ATank::Fire(){
	
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (ensure(Barrel != nullptr)) {
		if (IsReloaded) {
			auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
			auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
			FActorSpawnParameters SpawnParameters;
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,ProjectileLocation, ProjectileRotation,SpawnParameters);

			Projectile->LaunchProjectile(LauchSpeed);

			LastFireTime = FPlatformTime::Seconds();

		}
	}

}
