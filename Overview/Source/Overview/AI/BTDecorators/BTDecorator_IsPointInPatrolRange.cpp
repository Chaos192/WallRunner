// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsPointInPatrolRange.h"
#include "Overview/AI/BumpBallAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UBTDecorator_IsPointInPatrolRange::UBTDecorator_IsPointInPatrolRange() 
{
	NodeName = "Is Player In Patrol Range?";
}

bool UBTDecorator_IsPointInPatrolRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ABumpBallAIController* AIController = Cast<ABumpBallAIController>(OwnerComp.GetAIOwner());

	float Radius = AIController->GetPatrolRadius();
	FVector Origin = AIController->GetPatrolOrigin();
	FVector PlayerLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();

	float Distance = FVector::Dist2D(PlayerLoc, Origin);

	return (Distance < Radius);
}