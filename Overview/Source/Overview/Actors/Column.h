// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Column.generated.h"

UCLASS()
class OVERVIEW_API AColumn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColumn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlapOuter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBeginOverlapInner(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent)
	void MoveColumnOuter(FVector Loc);
	UFUNCTION(BlueprintNativeEvent)
	void MoveColumnInner(FVector Loc);
	UFUNCTION(BlueprintNativeEvent)
	void ChangeColor(float alpha);
	UFUNCTION() // Gets current direction of column movement : Should it decrease ZLoc or increase it
	void GetDirection(ABallCharacter * Player);

	UFUNCTION()
	void RestartInnerCollision();
	UFUNCTION()
	void RestartOuterCollision();

private:
	bool ZIncreasing;

	void ChangeColorForAttachedActors(float Alpha);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
	UStaticMeshComponent* ColumnMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UBoxComponent* OuterCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components)
	UBoxComponent* InnerCollision;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	float ZStepIncrease = 70;
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	float ZStepDecrease = 100;

	UPROPERTY(EditDefaultsOnly,Category = Color)
	float MaxZ;

	UPROPERTY(EditDefaultsOnly,Category = Restart)
	float RestartTime = 10;
	FTimerHandle RestartInnerTimer;
	FTimerHandle RestartOuterTimer;

};
