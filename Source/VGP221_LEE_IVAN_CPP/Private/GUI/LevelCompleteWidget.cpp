#include "GUI/LevelCompleteWidget.h"

void ULevelCompleteWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!ButtonWidgetPrefab) return;

    // Manually iterate through the enum values
    TArray<EButtonActionType> ButtonActions = {
        EButtonActionType::MainMenu,
        EButtonActionType::Quit,
    };

    for (EButtonActionType Action : ButtonActions)
    {
        FString ButtonText;
        switch (Action)
        {
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
