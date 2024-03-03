#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Starting FPS Map")));

	//InitializeMainMenu(MainMenuPrefab);
	ChangeMenuWidget(UserWidgetPrefab);
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
		InitializeUIControl();
	}
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
		InitializeGameInput();
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
		InitializeGameInput();
	}
	else
	{
		ShowPauseMenu(PC);
	}
}

void AFPSGamemode::ShowPauseMenu(APlayerController* PC)
{
	if (!CurrentPauseMenuWidget && PauseMenuPrefab)
	{
		CurrentPauseMenuWidget = CreateWidget<UPauseMenuWidget>(PC, PauseMenuPrefab);
		if (CurrentPauseMenuWidget)
		{
			CurrentPauseMenuWidget->AddToViewport();
			InitializeUIControl();
		}
	}
}

void AFPSGamemode::HidePauseMenu()
{
	if (CurrentPauseMenuWidget)
	{
		CurrentPauseMenuWidget->RemoveFromParent();
		CurrentPauseMenuWidget = nullptr;
	}
}

void AFPSGamemode::InitializeGameInput()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void AFPSGamemode::InitializeUIControl()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}
