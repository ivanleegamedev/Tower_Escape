#include "GUI/ButtonWidget.h"

void UButtonWidget::InitializeButton(const FString& InButtonText, EButtonActionType InActionType)
{
	if(!Button || !ButtonText) return;

	ButtonText->SetText(FText::FromString(InButtonText));
	ButtonActionType = InActionType;
	Button->OnClicked.AddDynamic(this, &UButtonWidget::OnButtonClick);
}

void UButtonWidget::OnButtonClick()
{
	switch (ButtonActionType)
	{
	case EButtonActionType::Restart:
		// Restart Game by restarting level
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Restart Button Clicked")));
		break;
	case EButtonActionType::MainMenu:
		// Go to Main Menu
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("MainMenu Button Clicked")));
		break;
	case EButtonActionType::Quit:
		// Quit Game
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Quit Button Clicked")));
		break;
	}
}
