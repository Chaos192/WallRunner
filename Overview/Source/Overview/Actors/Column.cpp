// Fill out your copyright notice in the Description page of Project Settings.


#include "Column.h"
#include "Overview/Pawns/BallCharacter.h"
#include "Overview/Interface/ColumnInterface.h"

// Sets default values
AColumn::AColumn()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	ColumnMesh = CreateDefaultSubobject<UStaticMeshComponent>("ColumnMesh");
	OuterCollision = CreateDefaultSubobject<UBoxComponent>("OuterCollision");
	InnerCollision = CreateDefaultSubobject<UBoxComponent>("InnerCollision");

	SetRootComponent(Scene);
	ColumnMesh->SetupAttachment(Scene);
	OuterCollision->SetupAttachment(ColumnMesh);
	InnerCollision->SetupAttachment(ColumnMesh);

	ColumnMesh->SetCollisionResponseToAllChannels(ECR_Block);
	OuterCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	OuterCollision->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	InnerCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InnerCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AColumn::BeginPlay()
{
	Super::BeginPlay();

	// Binding functions to execute when column is being overlapped
	OuterCollision->OnComponentBeginOverlap.AddDynamic(this, &AColumn::OnBeginOverlapOuter);
	InnerCollision->OnComponentBeginOverlap.AddDynamic(this, &AColumn::OnBeginOverlapInner);
	
}

void AColumn::OnBeginOverlapOuter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABallCharacter* Player = Cast<ABallCharacter>(OtherActor);

	if (Player) // Check if column was overlapped by Player
	{
		GetDirection(Player);
		FVector EndLocation = GetActorLocation();
		EndLocation.Z = (ZIncreasing) ? Player->GetActorLocation().Z : Player->GetActorLocation().Z - ZStepDecrease;

		MoveColumnOuter(EndLocation);

		float ColorAlpha = EndLocation.Z / MaxZ;
		ChangeColor(ColorAlpha);
		ChangeColorForAttachedActors(ColorAlpha);

		OuterCollision->OnComponentBeginOverlap.RemoveAll(this); // Restrict column movement by this function until restarting
		GetWorldTimerManager().SetTimer(RestartOuterTimer, this, &AColumn::RestartOuterCollision, RestartTime, false, RestartTime);
	}
}

void AColumn::OnBeginOverlapInner(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABallCharacter* Player = Cast<ABallCharacter>(OtherActor);

	if (Player) // Check if column was overlapped by Player
	{
		FVector StartLocation = GetActorLocation();
		FVector EndLocation = StartLocation;
		EndLocation.Z += (ZIncreasing) ? ZStepIncrease : - ZStepDecrease;

		MoveColumnInner(EndLocation);

		float ColorAlpha = EndLocation.Z / MaxZ;
		ChangeColor(ColorAlpha);
		ChangeColorForAttachedActors(ColorAlpha);

		InnerCollision->OnComponentBeginOverlap.RemoveAll(this); // Restrict column movement by this function until restarting
		GetWorldTimerManager().SetTimer(RestartInnerTimer, this, &AColumn::RestartInnerCollision, RestartTime, false, RestartTime);	
	}
}

void AColumn::GetDirection(ABallCharacter* Player)
{
	ZIncreasing = Player->GetZIncreasingSign();
}

void AColumn::ChangeColorForAttachedActors(float Alpha) 
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	// Change color of all attached to column actors that are inherited from IColumnInterface
	for (auto Actor : AttachedActors)
	{
		auto ColumnInterface = Cast<IColumnInterface>(Actor);
		if (ColumnInterface)
			ColumnInterface->Execute_ChangeColor(Actor,Alpha); // NOTE : when using interfaces, remember to call Execute_FuncName() not just FuncName(), or you will crash engine
	}
}

void AColumn::RestartInnerCollision() 
{
	if(GetActorLocation().Z < MaxZ)
		InnerCollision->OnComponentBeginOverlap.AddDynamic(this, &AColumn::OnBeginOverlapInner);
}

void AColumn::RestartOuterCollision() 
{
	if (GetActorLocation().Z < MaxZ)
		OuterCollision->OnComponentBeginOverlap.AddDynamic(this, &AColumn::OnBeginOverlapOuter);
}

void AColumn::MoveColumnOuter_Implementation(FVector Loc)
{

}

void AColumn::MoveColumnInner_Implementation(FVector Loc)
{

}

void AColumn::ChangeColor_Implementation(float alpha) 
{

}