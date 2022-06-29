// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallCharacterBase.h"
#include "BallCharacter.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API ABallCharacter : public ABallCharacterBase
{
	GENERATED_BODY()
public:
	ABallCharacter();

	UFUNCTION(BlueprintCallable,Category = ColumnField)
	bool GetZIncreasingSign();
	
	virtual void Death_Implementation();

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void UpdateZChangeSign();

private:
	UPROPERTY(EditDefaultsOnly, Category = Components)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UCameraComponent* Camera;

	UPROPERTY()
	bool ZIncreasing = false;
	FTimerHandle UpdateZTimer;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	float ChanceOfChangingZSign = 30.f;
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	float UpdateSignRate = 3.f;
	
};
