// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsPointInPatrolRange.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API UBTDecorator_IsPointInPatrolRange : public UBTDecorator
{
	GENERATED_BODY()

public: 
	UBTDecorator_IsPointInPatrolRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
