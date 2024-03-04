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
	if (!GM) return;

	switch (ButtonActionType)
	{
	case EButtonActionType::Start:
		GM->ShowWidget(GM->UserHUDPrefab, true);
		break;
	case EButtonActionType::Resume:
		GM->ShowWidget(GM->UserHUDPrefab, true);
		break;
	case EButtonActionType::Restart:
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		break;
	case EButtonActionType::MainMenu:
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		break;
	case EButtonActionType::Quit:
		UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, true);
		break;
	}
}
