#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"
#include "GUI/FPSUserWidget.h"
#include "GUI/PauseMenuWidget.h"
#include "FPSGamemode.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API AFPSGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UFPSUserWidget> UserWidgetPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UPauseMenuWidget> PauseMenuPrefab;

	UPROPERTY()
	UFPSUserWidget* CurrentWidget;
	
	UPROPERTY()
	UPauseMenuWidget* CurrentPauseMenuWidget;

	UFUNCTION()
	void ChangeMenuWidget(TSubclassOf<UFPSUserWidget> NewWidgetClass);

	UFUNCTION()
	void TogglePauseMenu();

	UFUNCTION()
	void ShowPauseMenu(APlayerController* PC);

	UFUNCTION()
	void HidePauseMenu();

	UFUNCTION()
	void EnablePauseInput(APlayerController* PC);

	UFUNCTION()
	void DisablePauseInput(APlayerController* PC);
};
