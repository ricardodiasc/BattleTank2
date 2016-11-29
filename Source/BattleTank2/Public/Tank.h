// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category="Firing")
	float LauchSpeed = 10000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category="Setup")
	void SetBarrel(UStaticMeshComponent* Barrel);

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;
	
};
