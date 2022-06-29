// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallCharacterBase.h"
#include "Components/SphereComponent.h"
#include "BumpBallAI.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API ABumpBallAI : public ABallCharacterBase
{
	GENERATED_BODY()
public:
	ABumpBallAI();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool GetIsFalling();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsConeOverlappingPlayer();
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,Category = Bumping)
	void BumpPlayer(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Components)
	USceneComponent* EyesScene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* CheckCone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bumping)
	float ZDirectionPluser = 2;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = Bumping)
	float BumpStrength = 1000;
	

};
