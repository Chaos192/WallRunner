// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TurretProjectile.generated.h"

UCLASS()
class OVERVIEW_API ATurretProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AddDamageAndImpulseAtLocation(UPrimitiveComponent* Comp, FVector Location);
	UFUNCTION(BlueprintCallable,Category = Hit)
	void OnHit();


public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category = Material)
	void ChangeColor(float Alpha);
	void ChangeColor_Implementation(float Alpha);

protected:
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float Damage = 10.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Damage)
	float DamageRadius = 300.f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Damage)
	float DamageImpulseStrength = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly,Category = Impulse)
	float EdgeZValueForDirectionOfImpulse = 0.07;
	UPROPERTY(EditDefaultsOnly, Category = Impulse)
	float NewZValueForImpulseDirection = 0.05;

	UPROPERTY(BlueprintReadWrite,Category = Material)
	float CurrentAlpha = 0.7;

private:
	TArray<AActor*> DamagedActors;

};
