// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Overview/Pawns/BallCharacter.h"
#include "Overview/Actors/TurretProjectile.h"
#include "Overview/Interface/ColumnInterface.h"
#include "Turret.generated.h"

UCLASS()
class OVERVIEW_API ATurret : public AActor, public IColumnInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);
	void RotateTop(float DeltaTime);
	void CalculateTargetRandomRotation();
	void RotateTopToRandomPoint();
	void SetTimerForRandomRotation();
	void ClearTimerForRandomRotation();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category = Shoot)
	void Shoot();
	void Shoot_Implementation();

	void SetTimerForShooting();
	void ClearTimerForShooting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Material)
	void ChangeColor(float Alpha);
	virtual void ChangeColor_Implementation(float Alpha);

private:
	UPROPERTY()
	ABallCharacter* Player;

	FTimerHandle RandomRotationTimer;
	UPROPERTY()
	FRotator TargetRandomRotation = FRotator(0);

	FTimerHandle ShootTimer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USceneComponent* Scene;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components)
	USceneComponent* ProjectileScene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* Base;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* Top;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* Barrel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USphereComponent* OuterCollision;

	UPROPERTY(EditDefaultsOnly,Category = Rotation)
	float RotateSpeed = 7;

	UPROPERTY(EditDefaultsOnly,Category = Rotation)
	float PerformRandomRotationMaxTime = 5;
	UPROPERTY(EditDefaultsOnly, Category = Rotation)
	float PerformRandomRotationMinTime = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = Rotation)
	float MaxRotationOffset = 90;
	UPROPERTY(EditDefaultsOnly, Category = Rotation)
	float MinRotationOffset = -90;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Shooting)
	TSubclassOf<ATurretProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Shooting)
	float ShootRate = 3;

	UPROPERTY(BlueprintReadWrite,Category = Material)
	float CurrentAlpha = 0.7;
};
