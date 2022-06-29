// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RotateToPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Overview/AI/BumpBallAIController.h"

UBTTask_RotateToPoint::UBTTask_RotateToPoint() 
{
	NodeName = "Rotate To Point";
}

EBTNodeResult::Type UBTTask_RotateToPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABumpBallAIController* AIController = Cast<ABumpBallAIController>(OwnerComp.GetAIOwner());
	FVector Point = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

	AIController->RotateToPoint(Point);

	return EBTNodeResult::Succeeded;
}
