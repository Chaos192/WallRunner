// Fill out your copyright notice in the Description page of Project Settings.


#include "KeysWidget.h"

void UKeysWidget::UpdateCollectedKeys_Implementation(int Keys)
{
	this->CollectedKeys = Keys;
}

void UKeysWidget::SetKeysAmount(int KeysAmount)
{
	this->MaxKeys = KeysAmount;
}