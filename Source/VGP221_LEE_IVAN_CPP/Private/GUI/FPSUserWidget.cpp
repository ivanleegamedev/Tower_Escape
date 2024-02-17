#include "GUI/FPSUserWidget.h"

void UFPSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthBar(1.0f);
	SetScore(0);

	//if (ButtonWidgetPrefab) {
	//	for (int i = 0; i < 4; i++)
	//	{
	//		UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
	//		ButtonContainer->AddChildToVerticalBox(widget);

	//		UButtonWidget* button = Cast<UButtonWidget>(widget); // Get Component in Unity
	//		button->SetText(i);
	//	}
	//}
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