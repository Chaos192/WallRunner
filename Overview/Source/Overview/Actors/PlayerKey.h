// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Overview/Interface/ColumnInterface.h"
#include "PlayerKey.generated.h"

UCLASS()
class OVERVIEW_API APlayerKey : public AActor, public IColumnInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerKey();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = Game)
	void DestroyKey();
	void DestroyKey_Implementation();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = Color)
	void ChangeColor(float Alpha);
	virtual void ChangeColor_Implementation(float Alpha);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	UStaticMeshComponent* KeyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly,Category = Rotation)
	float TickYawRot;
	UPROPERTY(BlueprintReadWrite,Category = DestroyAnim)
	FVector StartLoc;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = DestroyAnim)
	float EndLocZOffset;
};
