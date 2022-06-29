// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_ConeCheckForPlayer.h"
#include "Overview/Pawns/BumpBallAI.h"
#include "Kismet/GameplayStatics.h"
#include "Overview/Pawns/BumpBallAI.h"
#include "AIController.h"

UBTDecorator_ConeCheckForPlayer::UBTDecorator_ConeCheckForPlayer() 
{
	NodeName = "Can See Player?";
}

bool UBTDecorator_ConeCheckForPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	ABumpBallAI* AIPawn = Cast<ABumpBallAI>(OwnerComp.GetAIOwner()->GetPawn());

	return AIPawn->IsConeOverlappingPlayer();
}