#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Starting FPS Map")));

	InitializeMainMenu(MainMenuPrefab);
	//ChangeMenuWidget(UserWidgetPrefab);
}

void AFPSGamemode::InitializeMainMenu(TSubclassOf<UMainMenuWidget> NewWidgetClass)
{
	if (MainMenuWidget != nullptr)
	{
		MainMenuWidget->RemoveFromParent();
		MainMenuWidget = nullptr;
	}

	if (MainMenuPrefab != nullptr)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), NewWidgetClass);
		MainMenuWidget->AddToViewport();
		InitializeModeUIOnly();
	}
}

void AFPSGamemode::ChangeMenuWidget(TSubclassOf<UFPSUserWidget> NewWidgetClass)
{
	if (FPSUserWidget != nullptr)
	{
		FPSUserWidget->RemoveFromParent();
		FPSUserWidget = nullptr;
	}

	if (UserWidgetPrefab != nullptr)
	{
		FPSUserWidget = CreateWidget<UFPSUserWidget>(GetWorld(), NewWidgetClass);
		FPSUserWidget->AddToViewport();
		InitializeModeGameOnly();
	}
}

void AFPSGamemode::TogglePauseMenu()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	bool bIsCurrentlyPaused = UGameplayStatics::IsGamePaused(GetWorld());
	UGameplayStatics::SetGamePaused(GetWorld(), !bIsCurrentlyPaused);

	if (bIsCurrentlyPaused)
	{
		HidePauseMenu();
		InitializeModeGameOnly();
	}
	else
	{
		ShowPauseMenu(PC);
	}
}

void AFPSGamemode::ShowPauseMenu(APlayerController* PC)
{
	if (!PauseMenuWidget && PauseMenuPrefab)
	{
		PauseMenuWidget = CreateWidget<UPauseMenuWidget>(PC, PauseMenuPrefab);
		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
			InitializeModeUIOnly();
		}
	}
}

void AFPSGamemode::HidePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;
	}
}

void AFPSGamemode::InitializeModeGameOnly()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void AFPSGamemode::InitializeModeUIOnly()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}
