#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GUI/ButtonWidget.h"
#include "FPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API UFPSUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar; // Make sure that "HealthBar" name matches the name of the HealthBar in the Widget

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText; // Make sure that "ScoreText" name matches the name of the Text in the Widget

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TurretCountText; // Make sure that "TurretCountText" name matches the name of the Text in the Widget

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer; // Make sure that "ButtonContainer" name matches the name of the VerticalBox in the Widget

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UButtonWidget> ButtonWidgetPrefab;

	UFUNCTION()
	void SetHealthBar(float percentage);

	UFUNCTION()
	void SetScore(int newScore);

	UFUNCTION()
	void SetTurretCount(int Remaining, int Total);

private:
	UPROPERTY()
	int UIScore = 0;
};
