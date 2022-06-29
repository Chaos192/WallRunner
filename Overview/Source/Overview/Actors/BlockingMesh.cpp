// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockingMesh.h"

// Sets default values
ABlockingMesh::ABlockingMesh()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(Collision);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);
	Collision->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

