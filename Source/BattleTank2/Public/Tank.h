// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

UCLASS()
class BATTLETANK2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category="Firing")
	float LauchSpeed = 4000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Setup")
	void SetBarrel(UTankBarrel* Barrel);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurret(UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void Fire();
protected:

	UTankAimingComponent* TankAimingComponent = nullptr;
	
};
