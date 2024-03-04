#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"
#include "GUI/MainMenuWidget.h"
#include "GUI/FPSUserWidget.h"
#include "GUI/PauseMenuWidget.h"
#include "GUI/GameOverWidget.h"
#include "GUI/LevelCompleteWidget.h"
#include "FPSGamemode.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API AFPSGamemode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int TotalTurrets = 0;

	UPROPERTY()
	int TurretsRemaining = 0;
	
public:
	virtual void StartPlay() override;

	UFUNCTION()
	void InitializeTurretCount();

	UFUNCTION()
	void TurretDestroyed();

	UFUNCTION()
	void UpdateTurretCountUI();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UMainMenuWidget> MainMenuPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UFPSUserWidget> UserHUDPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UPauseMenuWidget> PauseMenuPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UGameOverWidget> GameOverPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<ULevelCompleteWidget> LevelCompletePrefab;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY()
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY()
	UFPSUserWidget* UserHUDWidget;
	
	UPROPERTY()
	UPauseMenuWidget* PauseMenuWidget;

	UPROPERTY()
	UGameOverWidget* GameOverWidget;

	UPROPERTY()
	ULevelCompleteWidget* LevelCompleteWidget;

	UFUNCTION()
	void ShowWidget(TSubclassOf<UUserWidget> NewWidgetClass, bool bGameInputMode);

	UFUNCTION()
	void CleanupWidgets();
};
