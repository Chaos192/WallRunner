// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATurretProjectile::ATurretProjectile()
{

}

// Called when the game starts or when spawned
void ATurretProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretProjectile::AddDamageAndImpulseAtLocation(UPrimitiveComponent* Comp, FVector Location)
{
	AActor* DamagedActor = Comp->GetOwner();
	AController* InstigatorController = GetOwner()->GetInstigatorController();
	AActor* DamageCauser = GetOwner();
	float DistanceToComp = (Location - Comp->GetComponentLocation()).Length();

	if (!DamagedActors.Contains(DamagedActor))
	{
		UGameplayStatics::ApplyDamage(DamagedActor, Damage, InstigatorController, DamageCauser, DamageType); // Apply damage for every overlapped actor
		DamagedActors.Add(DamagedActor);

		ACharacter* Character = Cast<ACharacter>(DamagedActor);

		if (Character) // Launch player
		{
			FVector LaunchDirection = UKismetMathLibrary::GetDirectionUnitVector(Location, Character->GetActorLocation());

			if (LaunchDirection.Z < EdgeZValueForDirectionOfImpulse) 
			{
				LaunchDirection.Z = NewZValueForImpulseDirection;
				LaunchDirection.Normalize();
			}

			FVector LaunchVelocity = LaunchDirection * DamageImpulseStrength / DistanceToComp;
			Character->LaunchCharacter(LaunchVelocity, true, true);
		}
	}
}

void ATurretProjectile::OnHit()
{
	FVector Location = GetActorLocation();

	TArray<FHitResult> OutHits;
	FCollisionShape SphereCollision = FCollisionShape::MakeSphere(DamageRadius);

	bool Hitted = GetWorld()->SweepMultiByChannel(OutHits, Location, Location, FQuat(0), ECC_WorldDynamic, SphereCollision); // Get hit result sweeping by SphereCollision

	if (Hitted)
	{
		for (auto OutHit : OutHits)
		{
			AddDamageAndImpulseAtLocation(OutHit.GetComponent(), Location);
		}
		DamagedActors.Empty();
	}
	Destroy();
}

void ATurretProjectile::ChangeColor_Implementation(float Alpha)
{

}
