#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);
	SetScore(0);
	SetTurretCount(0, 0);
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

void UFPSUserWidget::SetTurretCount(int Remaining, int Total)
{
	if (TurretCountText)
	{
		FString TurretText = FString::Printf(TEXT("Turrets Remaining: %d/%d"), Remaining, Total);
		TurretCountText->SetText(FText::FromString(TurretText));
	}
}
