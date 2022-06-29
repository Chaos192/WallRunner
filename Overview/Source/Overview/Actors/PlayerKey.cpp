// Fill out your copyright notice in the Description page of Project Settings.


#include "Overview/Actors/PlayerKey.h"
#include "Overview/Pawns/BallCharacter.h"
#include "Overview/GameBase/OverviewGameModeBase.h"

// Sets default values
APlayerKey::APlayerKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("KeyMesh");
	Collision = CreateDefaultSubobject<USphereComponent>("Collision");

	SetRootComponent(Scene);
	KeyMesh->SetupAttachment(Scene);
	Collision->SetupAttachment(KeyMesh);

	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void APlayerKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, TickYawRot * DeltaTime, 0));
}

void APlayerKey::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ABallCharacter* Player = Cast<ABallCharacter>(OtherActor);

	if (Player) // If key was overlapped by player - show next key
	{
		AOverviewGameModeBase* GameMode = Cast<AOverviewGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			SetActorEnableCollision(false);
			GameMode->ShowNextKey();
			DestroyKey();
		}
	}
}

void APlayerKey::ChangeColor_Implementation(float Alpha)
{

}

void APlayerKey::DestroyKey_Implementation() 
{
	
}