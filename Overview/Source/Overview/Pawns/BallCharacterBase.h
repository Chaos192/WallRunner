// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BallCharacterBase.generated.h"

UCLASS()
class OVERVIEW_API ABallCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABallCharacterBase();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Game)
	void Death();
	void Death_Implementation();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveFB(float axis);
	UFUNCTION()
	void MoveRL(float axis);

	UFUNCTION(BlueprintCallable,Category = Rotation)
	FRotator GetBallRotation();
private:
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float Ratio;
	FVector HorizontalVelocity;
	float HorizontalSpeed;
	float RotationAmount;
	UWorld* World;

};
