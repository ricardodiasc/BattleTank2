// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankPlayerDelegate);


UCLASS()
class BATTLETANK2_API ATank : public APawn
{
	GENERATED_BODY()
	

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTankPlayerDelegate OnDeath;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float CurrentHealth = StartHealth;

	
};
