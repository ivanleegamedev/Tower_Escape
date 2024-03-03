#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Starting FPS Map")));

	ChangeMenuWidget(UserWidgetPrefab);
}

void AFPSGamemode::ChangeMenuWidget(TSubclassOf<UFPSUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (UserWidgetPrefab != nullptr)
	{
		CurrentWidget = CreateWidget<UFPSUserWidget>(GetWorld(), NewWidgetClass);
		CurrentWidget->AddToViewport();
	}
}

void AFPSGamemode::TogglePauseMenu()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        bool bIsCurrentlyPaused = UGameplayStatics::IsGamePaused(GetWorld());
        UGameplayStatics::SetGamePaused(GetWorld(), !bIsCurrentlyPaused);

        // Show or hide the pause menu based on the game's new pause state.
        if (bIsCurrentlyPaused)
        {
            // Game is now unpaused, so hide the pause menu.
            if (CurrentPauseMenuWidget)
            {
                CurrentPauseMenuWidget->RemoveFromViewport();
                CurrentPauseMenuWidget = nullptr; // Clear the reference.
            }
            PC->bShowMouseCursor = false;
            PC->SetInputMode(FInputModeGameOnly());
        }
        else
        {
            // Game is now paused, so show the pause menu.
            if (!CurrentPauseMenuWidget && PauseMenuPrefab)
            {
                CurrentPauseMenuWidget = CreateWidget<UPauseMenuWidget>(PC, PauseMenuPrefab);
                if (CurrentPauseMenuWidget)
                {
                    CurrentPauseMenuWidget->AddToViewport();
                    PC->bShowMouseCursor = true;
                    PC->SetInputMode(FInputModeUIOnly());
                }
            }
        }
    }
}
