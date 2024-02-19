// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDetectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UIDetectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VGP221_LEE_IVAN_CPP_API IIDetectable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Player")
	bool IsPlayerDetected();
};
