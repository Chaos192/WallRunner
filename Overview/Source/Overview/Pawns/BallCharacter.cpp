// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCharacter.h"
	#include "Kismet/GameplayStatics.h"

ABallCharacter::ABallCharacter() 
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);
}

void ABallCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}

void ABallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABallCharacter::BeginPlay() 
{
    Super::BeginPlay();
	GetWorldTimerManager().SetTimer(UpdateZTimer, this, &ABallCharacter::UpdateZChangeSign, UpdateSignRate, true);
}

void ABallCharacter::UpdateZChangeSign()
{
	if (rand() % 100 < ChanceOfChangingZSign)
	{
		ZIncreasing = !ZIncreasing;
	}
}

bool ABallCharacter::GetZIncreasingSign()
{
	return ZIncreasing;
}

void ABallCharacter::Death_Implementation() 
{
	Super::Death_Implementation();
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}