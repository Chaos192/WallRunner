// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskLookingAround.h"
#include "Overview/AI/BumpBallAIController.h"

UBTTaskLookingAround::UBTTaskLookingAround() 
{
	NodeName = "Looking Around";
}

EBTNodeResult::Type UBTTaskLookingAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABumpBallAIController* AIController = Cast<ABumpBallAIController>(OwnerComp.GetAIOwner());

	AIController->LookAround();

	return EBTNodeResult::Succeeded;
}
