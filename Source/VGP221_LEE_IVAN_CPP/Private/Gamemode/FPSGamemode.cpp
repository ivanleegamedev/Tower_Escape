// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay();

	// Log to Screen
	// C Assert
	check(GEngine != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Starting FPS Map")));

	UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map"));
}
