// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNewPatrolPoint.h"
#include "Overview/AI/BumpBallAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Overview/GameBase/OverviewGameModeBase.h"
#include "GameFramework/GameMode.h"

UBTTask_FindNewPatrolPoint::UBTTask_FindNewPatrolPoint() 
{
	NodeName = "Find New Patrol Point";
}

EBTNodeResult::Type UBTTask_FindNewPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABumpBallAIController* AIController = Cast<ABumpBallAIController>(OwnerComp.GetAIOwner());
	APawn* Pawn = AIController->GetPawn();
	FVector Origin = AIController->GetPatrolOrigin();
	float Radius = AIController->GetPatrolRadius();

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		FVector ResultLoc = Cast<AOverviewGameModeBase>(GameMode)->GetRandomLocationInColumnField();
		if (ResultLoc == FVector::ZeroVector || UKismetMathLibrary::Vector_Distance2D(ResultLoc,Origin) > Radius) // If found point is not in patrol range task will fail but will be called again in behavior tree
		{
			return EBTNodeResult::Failed; 
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ResultLoc);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
