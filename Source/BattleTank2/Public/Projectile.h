// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK2_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LaunchProjectile(float Speed);

	UPROPERTY(VisibleAnywhere, Category="Particle Components")
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere, Category = "Particle Components")
	UParticleSystemComponent* LaunchBlast;

	UPROPERTY(VisibleAnywhere, Category = "Particle Components")
	UParticleSystemComponent* ImpactBlast;
	
private: 
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
};
