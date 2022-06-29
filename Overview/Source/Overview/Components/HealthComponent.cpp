// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Overview/GameBase/OverviewGameModeBase.h"
#include "Overview/Pawns/BallCharacter.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeAnyDamage);
}

void UHealthComponent::TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetOwner() && !Dead)
	{
		CurrentHealth -= Damage;

		if (CurrentHealth <= 0)
		{
			Death();
		}
	}
}

void UHealthComponent::Death() 
{
	Dead = true;

	GetOwner()->OnTakeAnyDamage.Clear(); // Unbind take damage event from owner

	ABallCharacterBase* BaseCharacter = Cast<ABallCharacterBase>(GetOwner());
	BaseCharacter->Death();

	ABallCharacter* Player = Cast<ABallCharacter>(BaseCharacter);

	if (Player) // End game if it was the player who died
	{
		AOverviewGameModeBase* GameMode = Cast<AOverviewGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->EndGame();
	}
}
