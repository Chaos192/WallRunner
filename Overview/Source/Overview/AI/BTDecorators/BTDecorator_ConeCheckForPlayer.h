// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ConeCheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API UBTDecorator_ConeCheckForPlayer : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_ConeCheckForPlayer();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
