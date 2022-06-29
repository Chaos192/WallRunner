// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BlockingMesh.generated.h"

UCLASS()
class OVERVIEW_API ABlockingMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockingMesh();

protected:
	UPROPERTY(EditDefaultsOnly,Category = Components)
	UBoxComponent* Collision;
};
