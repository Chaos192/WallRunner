// Fill out your copyright notice in the Description page of Project Settings.


#include "BumpBallAI.h"
#include "Overview/AI/BumpBallAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Overview/Pawns/BallCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ABumpBallAI::ABumpBallAI() 
{
	EyesScene = CreateDefaultSubobject<USceneComponent>("Scene");
	CheckCone = CreateDefaultSubobject<UStaticMeshComponent>("CheckCone");

	EyesScene->SetupAttachment(GetRootComponent());
	CheckCone->SetupAttachment(EyesScene);

	CheckCone->SetCollisionResponseToAllChannels(ECR_Ignore);
	CheckCone->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);

	CheckCone->SetHiddenInGame(true);
}

void ABumpBallAI::BeginPlay() 
{
	Super::BeginPlay();
	ABumpBallAIController* AIController = Cast<ABumpBallAIController>(GetController());
	if (AIController)
	{
		AIController->SetPatrolOrigin(GetActorLocation());
	}
}

void ABumpBallAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ABumpBallAI::GetIsFalling() 
{
	return GetCharacterMovement()->IsFalling();
}

bool ABumpBallAI::IsConeOverlappingPlayer() 
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	return CheckCone->IsOverlappingActor(Player);
}

void ABumpBallAI::BumpPlayer(AActor* OtherActor) 
{
	ABallCharacter* Player = Cast<ABallCharacter>(OtherActor);
	if (Player)
	{
		FVector LaunchDirection = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), Player->GetActorLocation());
		LaunchDirection.Z += ZDirectionPluser;
		FVector LaunchVelocity = LaunchDirection * BumpStrength;

		Player->LaunchCharacter(LaunchVelocity, true, true);
	}
}