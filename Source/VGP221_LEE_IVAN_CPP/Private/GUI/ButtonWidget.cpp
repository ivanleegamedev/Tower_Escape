#include "GUI/ButtonWidget.h"
#include "Gamemode/FPSGamemode.h"

void UButtonWidget::InitializeButton(const FString& InButtonText, EButtonActionType InActionType)
{
	if(!Button || !ButtonText) return;

	ButtonText->SetText(FText::FromString(InButtonText));
	ButtonActionType = InActionType;
	Button->OnClicked.AddDynamic(this, &UButtonWidget::OnButtonClick);
}

void UButtonWidget::OnButtonClick()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	AFPSGamemode* GM = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	switch (ButtonActionType)
	{
	case EButtonActionType::Resume:
		if (GM) GM->TogglePauseMenu();
		break;
	case EButtonActionType::Restart:
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		break;
	case EButtonActionType::MainMenu:
		// Go to Main Menu
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("MainMenu Button Clicked")));
		break;
	case EButtonActionType::Quit:
		UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
		break;
	}
}
