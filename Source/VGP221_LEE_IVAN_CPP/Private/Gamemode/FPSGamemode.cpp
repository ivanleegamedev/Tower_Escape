#include "Gamemode/FPSGamemode.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Starting FPS Map")));

	ShowWidget(MainMenuPrefab, false);
	//ChangeMenuWidget(UserWidgetPrefab);
}

void AFPSGamemode::ShowWidget(TSubclassOf<UUserWidget> NewWidgetClass, bool bGameInputMode)
{
	CleanupWidgets();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = !bGameInputMode;

		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (NewWidget)
		{
			NewWidget->AddToViewport();
		}

		FInputModeUIOnly UIInputMode;
		FInputModeGameOnly GameInputMode;

		if (bGameInputMode)
		{
			PC->SetInputMode(GameInputMode);
			UGameplayStatics::SetGamePaused(GetWorld(), false);
		}
		else
		{
			PC->SetInputMode(UIInputMode);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		
		CurrentWidget = NewWidget;
	}
}

void AFPSGamemode::CleanupWidgets()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
}
