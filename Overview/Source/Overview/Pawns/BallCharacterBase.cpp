// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABallCharacterBase::ABallCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->AirControl = 0.3;

}

// Called when the game starts or when spawned
void ABallCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
}

// Called every frame
void ABallCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ABallCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveFB", this, &ABallCharacterBase::MoveFB);
	PlayerInputComponent->BindAxis("MoveRL", this, &ABallCharacterBase::MoveRL);
	PlayerInputComponent->BindAxis("LookUD", this, &ABallCharacterBase::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRL", this, &ABallCharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallCharacterBase::Jump);

}

void ABallCharacterBase::MoveFB(float axis)
{
	AddMovementInput(GetActorForwardVector(), axis);
}

void ABallCharacterBase::MoveRL(float axis)
{
	AddMovementInput(GetActorRightVector(), axis);
}

FRotator ABallCharacterBase::GetBallRotation()
{
	float DeltaTime = World->GetDeltaSeconds();
	HorizontalVelocity = GetVelocity();
	HorizontalVelocity.Z = 0;
	HorizontalSpeed = HorizontalVelocity.Size();
	
	RotationAmount += (HorizontalSpeed / (3.14 * Ratio) * DeltaTime);
	HorizontalVelocity.Normalize();

	FRotator Rotated = UKismetMathLibrary::MakeRotFromX(HorizontalVelocity);
	FVector RightVector = UKismetMathLibrary::GetRightVector(Rotated);

	return UKismetMathLibrary::RotatorFromAxisAndAngle(RightVector, RotationAmount);
}

void ABallCharacterBase::Death_Implementation() 
{

}