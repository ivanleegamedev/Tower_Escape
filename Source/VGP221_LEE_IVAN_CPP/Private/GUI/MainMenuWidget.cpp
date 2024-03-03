#include "GUI/MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!ButtonWidgetPrefab) return;

    // Manually iterate through the enum values
    TArray<EButtonActionType> ButtonActions = {
        EButtonActionType::Start,
        EButtonActionType::Quit,
    };

    for (EButtonActionType Action : ButtonActions)
    {
        FString ButtonText;
        switch (Action)
        {
        case EButtonActionType::Start:
            ButtonText = "Start";
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
