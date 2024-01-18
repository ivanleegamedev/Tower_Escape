// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay(); // Calls base function similar to the base function in Unity.

	if (GEngine != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Starting FPS Map")));
	}

	// C Assert
	// If this fails throw an error
	// check(GEngine != nullptr)
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Starting FPS Map")));

	// int test = 10;
	// bool boolTest = true;
	// UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map %i %d"), boolTest, test);

	// UE_LOGFMT(LogTemp, Warning, "This is an int {TheInt}", ("TheInt", test));
}
