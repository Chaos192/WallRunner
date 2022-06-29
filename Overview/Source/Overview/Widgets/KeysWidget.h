// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeysWidget.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API UKeysWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCollectedKeys(int Keys);
	void UpdateCollectedKeys_Implementation(int Keys);
	UFUNCTION()
	void SetKeysAmount(int KeysAMount);

protected:
	UPROPERTY(BlueprintReadOnly,Category = Keys)
	int CollectedKeys = 0;
	UPROPERTY(BlueprintReadOnly, Category = Keys)
	int MaxKeys;
	
};
