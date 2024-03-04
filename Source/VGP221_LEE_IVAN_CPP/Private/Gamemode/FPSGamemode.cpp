#include "Gamemode/FPSGamemode.h"
#include "Turrets/BasicTurret.h"

void AFPSGamemode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Starting FPS Map")));

	InitializeTurretCount();
	ShowWidget(MainMenuPrefab, false);
}

void AFPSGamemode::InitializeTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicTurret::StaticClass(), TurretActors);
	TotalTurrets = TurretActors.Num();
	TurretsRemaining = TotalTurrets;
	UpdateTurretCountUI();
}

void AFPSGamemode::TurretDestroyed()
{
	if (TurretsRemaining > 0)
	{
		TurretsRemaining--;
		UpdateTurretCountUI();
		
		if (TurretsRemaining == 0)
		{
			ShowWidget(LevelCompletePrefab, false);
		}
	}
}

void AFPSGamemode::UpdateTurretCountUI()
{
	if (UserHUDWidget)
	{
		UserHUDWidget->SetTurretCount(TurretsRemaining, TotalTurrets);
	}
}

void AFPSGamemode::ShowWidget(TSubclassOf<UUserWidget> NewWidgetClass, bool bGameInputMode)
{
	CleanupWidgets();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
	if (NewWidget)
	{
		NewWidget->AddToViewport();
		CurrentWidget = NewWidget;

		if (NewWidgetClass == UserHUDPrefab)
		{
			UserHUDWidget = Cast<UFPSUserWidget>(NewWidget);
			UpdateTurretCountUI();
		}

		PC->bShowMouseCursor = !bGameInputMode;
		FInputModeGameOnly GameInputMode;
		FInputModeUIOnly UIInputMode;

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
