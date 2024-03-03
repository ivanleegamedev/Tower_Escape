#include "GUI/PauseMenuWidget.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (!ButtonWidgetPrefab) return;

    // Manually iterate through the enum values
    TArray<EButtonActionType> ButtonActions = {
        EButtonActionType::Resume,
        EButtonActionType::Restart,
        EButtonActionType::MainMenu,
        EButtonActionType::Quit,
    };

    for (EButtonActionType Action : ButtonActions)
    {
        FString ButtonText;
        switch (Action)
        {
            case EButtonActionType::Resume:
                ButtonText = "Resume";
                break;
            case EButtonActionType::Restart:
                ButtonText = "Restart";
                break;
            case EButtonActionType::MainMenu:
                ButtonText = "Main Menu";
                break;
            case EButtonActionType::Quit:
                ButtonText = "Quit";
                break;
        }

        UButtonWidget* ButtonWidget = CreateWidget<UButtonWidget>(this, ButtonWidgetPrefab);
        if (ButtonWidget && ButtonContainer)
        {
            ButtonWidget->InitializeButton(ButtonText, Action);
            ButtonContainer->AddChildToVerticalBox(ButtonWidget);
        }
    }
}
