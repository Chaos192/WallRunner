// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Overview/Actors/Column.h"
#include "Overview/Actors/PlayerKey.h"
#include "Overview/Actors/Turret.h"
#include "Overview/Widgets/KeysWidget.h"
#include "Overview/Widgets/EndGameWidget.h"
#include "Overview/Pawns/BumpBallAI.h"
#include "OverviewGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API AOverviewGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = Keys)
	void HideAllKeys();
	UFUNCTION(BlueprintCallable, Category = Keys)
	void ShowNextKey();

	UFUNCTION(BlueprintCallable, Category = Navigation)
	FVector GetRandomLocationInColumnField();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = Navigation)
	float GetDistanceBetweenColumns();

	UFUNCTION(BlueprintCallable,Category = EndGame)
	void EndGame();
	UFUNCTION(BlueprintCallable, Category = EndGame)
	void EnableSpectatorMode();
	UFUNCTION(BlueprintCallable, Category = EndGame)
	void RestartGame();


protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void GenerateColumnField();


protected:
	UPROPERTY(EditDefaultsOnly,Category = Columns)
	int AmountOfColumns = 100;
	UPROPERTY(EditDefaultsOnly,Category = Columns)
	float DistanceBetweenColumns = 20;
	UPROPERTY(EditDefaultsOnly,Category = Columns)
	TSubclassOf<AColumn> ColumnClass;

	UPROPERTY(EditDefaultsOnly, Category = Keys)
	TSubclassOf<APlayerKey> PlayerKeyClass;
	UPROPERTY(EditDefaultsOnly,Category = Keys)
	int KeysAmount = 7;

	UPROPERTY(EditDefaultsOnly, Category = Turrets)
	TSubclassOf<ATurret> TurretClass;
	UPROPERTY(EditDefaultsOnly, Category = Turrets)
	int TurretsAmount = 7;

	UPROPERTY(EditDefaultsOnly,Category = AI)
	TSubclassOf<ABumpBallAI> AIClass;
	UPROPERTY(EditDefaultsOnly, Category = AI)
	int AIAmount = 10;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UKeysWidget> KeysWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category = Widgets)
	UKeysWidget* KeysWidget;
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UEndGameWidget> EndGameWidgetClass;
	UPROPERTY(BlueprintReadOnly, Category = Widgets)
	UEndGameWidget* EndGameWidget;

private:
	UPROPERTY()
	TArray<AActor*> Columns;
	UPROPERTY()
	TArray<int> ChosenIndexes;
	UPROPERTY()
	TArray<AActor*> Keys;
	UPROPERTY()
	int CurrentKeyIndex = 0;

	UPROPERTY()
	int BlockingVolumeCount = 4;
};
