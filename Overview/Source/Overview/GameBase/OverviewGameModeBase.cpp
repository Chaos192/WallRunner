// Copyright Epic Games, Inc. All Rights Reserved.


#include "OverviewGameModeBase.h"
#include "Overview/Actors/BlockingMesh.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpectatorPawn.h"


void AOverviewGameModeBase::BeginPlay() 
{
	Super::BeginPlay();

	GenerateColumnField();

	if (KeysWidgetClass)
	{
		KeysWidget = CreateWidget<UKeysWidget>(GetWorld(), KeysWidgetClass);
		if (KeysWidget)
		{
			KeysWidget->SetKeysAmount(KeysAmount);
			KeysWidget->AddToViewport(0);
		}
	}

	return;
}

void AOverviewGameModeBase::GenerateColumnField() 
{
	for (int i = 0;i < BlockingVolumeCount;i++) // Spawn blocking volumes around field
	{
		float X = 0;
		float Y = 0;
		float Z = 0;
		FRotator Rotation(0);

		switch (i)
		{
		case 0:
			X = (AmountOfColumns + 1) * DistanceBetweenColumns / 2;
			Y = DistanceBetweenColumns / 3;
			Rotation = FRotator(0, 90, 0);
			break;
		case 1:
			X = (AmountOfColumns + 1) * DistanceBetweenColumns - DistanceBetweenColumns / 3;
			Y = (AmountOfColumns + 1) * DistanceBetweenColumns / 2 - DistanceBetweenColumns / 3;
			break;
		case 2:
			X = (AmountOfColumns + 1) * DistanceBetweenColumns / 2 - DistanceBetweenColumns / 3;
			Y = (AmountOfColumns + 1) * DistanceBetweenColumns - DistanceBetweenColumns / 3;
			Rotation = FRotator(0, -90, 0);
			break;
		case 3:
			X = DistanceBetweenColumns / 3;
			Y = (AmountOfColumns + 1) * DistanceBetweenColumns / 2;
			break;
		}

		FVector Location(X, Y, Z);
		FVector Scale(1, DistanceBetweenColumns * AmountOfColumns / 50, 1000);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* BlockingMesh = GetWorld()->SpawnActor<ABlockingMesh>(ABlockingMesh::StaticClass(), Location, Rotation, SpawnParams);
		BlockingMesh->SetActorScale3D(Scale);
	}

	if(ColumnClass)
	for (int i = 0;i < AmountOfColumns;i++) // Spawn columns
	{
		for (int j = 0;j < AmountOfColumns;j++) 
		{
			FVector Location((i + 1) * DistanceBetweenColumns,(j + 1) * DistanceBetweenColumns,0);
			FRotator Rotation(0);
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AActor* Column = GetWorld()->SpawnActor<AColumn>(ColumnClass, Location, Rotation, SpawnParams);

			Columns.Add(Column);
		}
	}

	int ColumnsCount = Columns.Num();

	if(PlayerKeyClass)
	for (int i = 0;i < KeysAmount;i++) // Spawn keys
	{
		int index;

		do 
		{
			index = rand() % ColumnsCount;
		} while (ChosenIndexes.Contains(index));

		ChosenIndexes.Add(index);

		FVector Location = Columns[index]->GetActorLocation();
		FRotator Rotation(0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* Key = GetWorld()->SpawnActor<APlayerKey>(PlayerKeyClass, Location, Rotation, SpawnParams);

		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative,false);
		Key->AttachToActor(Columns[index],AttachRules);

		Keys.Add(Key);
	}

	HideAllKeys();
	ShowNextKey();

	if(TurretClass)
	for (int i = 0; i < TurretsAmount; i++) // Spawn turrets
	{
		int index;

		do
		{
			index = rand() % ColumnsCount;
		} while (ChosenIndexes.Contains(index));

		ChosenIndexes.Add(index);

		FVector Location = Columns[index]->GetActorLocation();
		FRotator Rotation(0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* Turret = GetWorld()->SpawnActor<ATurret>(TurretClass, Location, Rotation, SpawnParams);

		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);
		Turret->AttachToActor(Columns[index], AttachRules);
	}

	if(AIClass)
	for (int i = 0; i < AIAmount; i++) // Spawn AI
	{
		int index;

		do
		{
			index = rand() % ColumnsCount;
		} while (ChosenIndexes.Contains(index));

		ChosenIndexes.Add(index);

		FVector Location = Columns[index]->GetActorLocation();
		FRotator Rotation(0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* AI = GetWorld()->SpawnActor<ABumpBallAI>(AIClass, Location, Rotation, SpawnParams);
		AI->AddActorLocalOffset(FVector(0, 0, 50)); // Adjust AI location
	}
}

void AOverviewGameModeBase::HideAllKeys() 
{
	for (auto Key : Keys) 
	{
		Key->SetActorHiddenInGame(true);
		Key->SetActorEnableCollision(false);
	}
}

void AOverviewGameModeBase::ShowNextKey() 
{
	if (KeysWidget)
		KeysWidget->UpdateCollectedKeys(CurrentKeyIndex);

	if (CurrentKeyIndex < KeysAmount)
	{
		Keys[CurrentKeyIndex]->SetActorHiddenInGame(false);
		Keys[CurrentKeyIndex]->SetActorEnableCollision(true);
		CurrentKeyIndex++;
	}
	else 
	{
		EndGame();
	}
}

FVector AOverviewGameModeBase::GetRandomLocationInColumnField() 
{
	if (Columns.Num() > 0)
	{
		int Index = rand() % Columns.Num();
		return Columns[Index]->GetActorLocation();
	}
	else 
	{
		return FVector::ZeroVector;
	}
}

float AOverviewGameModeBase::GetDistanceBetweenColumns() 
{
	return DistanceBetweenColumns;
}

void AOverviewGameModeBase::EndGame() 
{
	ABallCharacterBase* Player = Cast<ABallCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		Player->DisableInput(Cast<APlayerController>(Player->GetController()));
		Player->OnTakeAnyDamage.Clear(); // Unbind take damage event from owner
	}

	KeysWidget->RemoveFromParent();

	if (EndGameWidgetClass)
	{
		EndGameWidget = CreateWidget<UEndGameWidget>(GetWorld(), EndGameWidgetClass);
		EndGameWidget->AddToViewport(0);
	}
}

void AOverviewGameModeBase::EnableSpectatorMode() 
{
	// Spawn and possess into spectator pawn

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerCameraManager* Camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	FVector Loc = Camera->GetCameraLocation();
	FRotator Rot = Camera->GetCameraRotation();
	FActorSpawnParameters SpawnParams;

	ASpectatorPawn* Spectator = GetWorld()->SpawnActor<ASpectatorPawn>(ASpectatorPawn::StaticClass(), Loc, Rot, SpawnParams);

	Player->GetController()->Possess(Spectator);
}

void AOverviewGameModeBase::RestartGame() 
{
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(),true);
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName), true); // Reopen level for resetting game
}