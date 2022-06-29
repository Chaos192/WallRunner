// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BumpBallAIController.generated.h"

/**
 * 
 */
UCLASS()
class OVERVIEW_API ABumpBallAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABumpBallAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category = Patrol)
	void SetPatrolOrigin(FVector Loc);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Patrol)
	FVector GetPatrolOrigin();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Patrol)
	float GetPatrolRadius();

	UFUNCTION(BlueprintCallable,Category = Jump)
	void JumpOverObstacle(FHitResult& Hit);

 	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Rotation)
 	void LookAround();
	void LookAround_Implementation();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category = Rotation)
	void RotateToPoint(FVector Point);
	void RotateToPoint_Implementation(FVector Point);

	UFUNCTION(BlueprintCallable,Category = Navigation)
	void MoveAITo(AActor* TargetActor,FVector TargetLocation,float AcceptableDistance);
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = Navigation)
	bool IsMoveToFinished();
	UFUNCTION(BlueprintCallable, Category = Navigation)
	void AbortMoveAITo();

protected:
	UPROPERTY(EditDefaultsOnly,Category = Patrol)
	float PatrolRadius = 500;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Patrol)
	float RotateAngle = 45;

	UPROPERTY(EditDefaultsOnly,Category = Jump)
	float DistanceToObstacleBeforeJump = 200;
	UPROPERTY(EditDefaultsOnly, Category = Jump)
	float HeightAboveObstacle = 200;
	UPROPERTY(EditDefaultsOnly, Category = Jump)
	float JumpZVelocity = 11;
	UPROPERTY(EditDefaultsOnly, Category = Jump)
	float JumpXYVelocity = 2;


private:
	void TickableMoveAITo();
	AActor* TargetActor;
	FVector TargetLocation;
	float AcceptableDistance;
	bool bIsMovingToTarget = false;
	bool bIsMoveToFinished = false;

	UPROPERTY(EditDefaultsOnly, Category = BehaviorTree)
	class UBehaviorTree* AIBehavior;

	UPROPERTY()
	FVector PatrolOrigin;
	UFUNCTION()
	FHitResult GetHitResultInFront();
	
};
