#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);
	SetScore(0);
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(percentage);
	}
}

void UFPSUserWidget::SetScore(int newScore)
{
	if(!ScoreText) return;

	UIScore += newScore;
	ScoreText->SetText(FText::FromString("Score: " + FString::FromInt(UIScore)));
}