#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay(); // Calls base function similar to the base function in Unity.

	// C Assert
	// If this fails throw an error
	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Starting FPS Map")));
	
	// Log to console
	// int test = 10;
	// bool boolTest = true;
	// UE_LOG(LogTemp, Warning, TEXT("Starting FPS Map %i %d"), boolTest, test);

	// Shortcut to log to console
	// NOTE: This is new so there could be issues
	// UE_LOGFMT(LogTemp, Warning, "This is an int {TheInt}", ("TheInt", test));

	ChangeMenuWidget(UserWidgetPrefab);
}

void AFPSGamemode::ChangeMenuWidget(TSubclassOf<UFPSUserWidget> NewWidgetClass)
{
	// 1. If we have one, remove it
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	// 2. If we don't have one, add it to the viewport
	if (UserWidgetPrefab != nullptr)
	{
		CurrentWidget = CreateWidget<UFPSUserWidget>(GetWorld(), NewWidgetClass);
		CurrentWidget->AddToViewport();
	}
}
