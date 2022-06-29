// Fill out your copyright notice in the Description page of Project Settings.


#include "BumpBallAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Overview/Pawns/BallCharacter.h"
#include "Overview/Pawns/BumpBallAI.h"
#include "NavigationSystem.h"

ABumpBallAIController::ABumpBallAIController() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABumpBallAIController::BeginPlay() 
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior); // Start AI logic
	}
}

void ABumpBallAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	FHitResult Hit = GetHitResultInFront();

	if (Hit.bBlockingHit) // Jump if something is in front of AI
	{
		ABumpBallAI* AICharacter = Cast<ABumpBallAI>(GetPawn());
		
		JumpOverObstacle(Hit);
	}

	if (bIsMovingToTarget) 
	{
		TickableMoveAITo(); // Analog of built in MoveTo function made for needs of project
	}
}

void ABumpBallAIController::SetPatrolOrigin(FVector Loc) 
{
	PatrolOrigin = Loc;
}

FVector ABumpBallAIController::GetPatrolOrigin() 
{
	return PatrolOrigin;
}

float ABumpBallAIController::GetPatrolRadius() 
{
	return PatrolRadius;
}

FHitResult ABumpBallAIController::GetHitResultInFront() 
{
	FVector StartLoc = GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * 30;
	FVector EndLoc = StartLoc + GetPawn()->GetActorForwardVector() * DistanceToObstacleBeforeJump;
	FHitResult OutHit;

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), StartLoc, EndLoc, 10, ETraceTypeQuery::TraceTypeQuery1, false, { GetPawn() }, EDrawDebugTrace::None, OutHit, true); 

	return OutHit;
}

void ABumpBallAIController::JumpOverObstacle(FHitResult& Hit) 
{
	FVector LaunchVelocity;
	FVector StartLocation = GetPawn()->GetActorLocation();
	FVector EndLocation = Hit.Location;
	EndLocation.Z = HeightAboveObstacle + Hit.GetActor()->GetActorLocation().Z;

	LaunchVelocity.X = (EndLocation.X - StartLocation.X) * JumpXYVelocity;
	LaunchVelocity.Y = (EndLocation.Y - StartLocation.Y) * JumpXYVelocity;
	LaunchVelocity.Z = (EndLocation.Z - StartLocation.Z) * JumpZVelocity;

	Cast<ACharacter>(GetPawn())->LaunchCharacter(LaunchVelocity,true,true);
}

void ABumpBallAIController::TickableMoveAITo()
{
	FVector Direction;

	FVector StartLoc = GetPawn()->GetActorLocation();
	FVector EndLoc = (TargetActor) ? TargetActor->GetActorLocation() : TargetLocation;
	Direction = UKismetMathLibrary::GetDirectionUnitVector(StartLoc, EndLoc);

	GetPawn()->AddMovementInput(Direction, 1, true);

	if (UKismetMathLibrary::Vector_Distance2D(StartLoc, EndLoc) <= AcceptableDistance)
	{
		bIsMovingToTarget = false;
		bIsMoveToFinished = true;
	}
}

void ABumpBallAIController::MoveAITo(AActor* Actor, FVector Location, float AcceptableRadius)
{
	// Function sets all variables needed for TickableMoveAITo

	TargetActor = Actor;
	TargetLocation = Location;
	AcceptableDistance = AcceptableRadius;
	bIsMovingToTarget = true;
	bIsMoveToFinished = false;
}

bool ABumpBallAIController::IsMoveToFinished()
{
	return bIsMoveToFinished;
}

void ABumpBallAIController::AbortMoveAITo() 
{
	bIsMovingToTarget = false;
	bIsMoveToFinished = true;
}

void ABumpBallAIController::LookAround_Implementation()
{

}

void ABumpBallAIController::RotateToPoint_Implementation(FVector Point)
{

}