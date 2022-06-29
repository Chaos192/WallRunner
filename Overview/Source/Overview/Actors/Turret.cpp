// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/KismetMathLibrary.h"
#include "Overview/Actors/Column.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Base = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	Top = CreateDefaultSubobject<UStaticMeshComponent>("TopMesh");
	Barrel = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	OuterCollision = CreateDefaultSubobject<USphereComponent>("Collision");
	ProjectileScene = CreateDefaultSubobject<USceneComponent>("BulletScene");

	SetRootComponent(Scene);
	Base->SetupAttachment(Scene);
	Top->SetupAttachment(Base);
	Barrel->SetupAttachment(Top);
	OuterCollision->SetupAttachment(Scene);
	ProjectileScene->SetupAttachment(Barrel);

	Base->SetCollisionResponseToAllChannels(ECR_Block);
	Top->SetCollisionResponseToAllChannels(ECR_Block);
	Barrel->SetCollisionResponseToAllChannels(ECR_Block);
	OuterCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	OuterCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	SetTimerForRandomRotation();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateTop(DeltaTime);
}

void ATurret::RotateTop(float DeltaTime) 
{
	if (Player) 
	{
		ClearTimerForRandomRotation();

		FVector Start = Top->GetComponentLocation();
		FVector Target = Player->GetActorLocation();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
		FRotator NewRotation = FMath::RInterpTo(Top->GetComponentRotation(), TargetRotation, DeltaTime, RotateSpeed);

		Top->SetWorldRotation(NewRotation);
	}
	else 
	{
		RotateTopToRandomPoint();
	}
}

void ATurret::NotifyActorBeginOverlap(AActor* OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ABallCharacter* PotentialPlayer = Cast<ABallCharacter>(OtherActor);
	if (PotentialPlayer)
	{
		Player = PotentialPlayer;
		SetTimerForShooting();
	}
}

void ATurret::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (Player)
	{
		if (Player == OtherActor)
		{
			Player = nullptr;
			SetTimerForRandomRotation();
			ClearTimerForShooting();
		}
	}
}

void ATurret::RotateTopToRandomPoint() 
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FRotator CurrentRotation = Top->GetComponentRotation();

	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRandomRotation, DeltaTime, RotateSpeed);
	Top->SetWorldRotation(NewRotation);
}

void ATurret::SetTimerForRandomRotation() 
{
	float Rate = FMath::RandRange(PerformRandomRotationMinTime, PerformRandomRotationMaxTime);
	GetWorldTimerManager().SetTimer(RandomRotationTimer, this, &ATurret::CalculateTargetRandomRotation, Rate, false);
}

void ATurret::ClearTimerForRandomRotation()
{
	GetWorldTimerManager().ClearTimer(RandomRotationTimer);
}

void ATurret::CalculateTargetRandomRotation() 
{
	TargetRandomRotation.Yaw = FMath::RandRange(MinRotationOffset, MaxRotationOffset);
	SetTimerForRandomRotation();
}

void ATurret::Shoot_Implementation() 
{
	if (Player)
	{
		FVector Location = ProjectileScene->GetComponentLocation();
		FRotator Rotation = Top->GetForwardVector().Rotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ATurretProjectile* Projectile = GetWorld()->SpawnActor<ATurretProjectile>(ProjectileClass, Location, Rotation, SpawnParams);
		Projectile->SetOwner(this);
		Projectile->ChangeColor(CurrentAlpha);
	}
}

void ATurret::SetTimerForShooting() 
{
	GetWorldTimerManager().SetTimer(ShootTimer,this, &ATurret::Shoot, ShootRate, true, ShootRate);
}

void ATurret::ClearTimerForShooting()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ATurret::ChangeColor_Implementation(float Alpha)
{

}

