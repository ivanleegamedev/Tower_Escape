#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonWidget.generated.h"

UENUM(BlueprintType)
enum class EButtonActionType : uint8
{
	Resume UMETA(DisplayName = "Resume"),
	Restart UMETA(DisplayName = "Restart"),
	MainMenu UMETA(DisplayName = "Main Menu"),
	Quit UMETA(DisplayName = "Quit"),
};

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
		
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	EButtonActionType ButtonActionType;

	UFUNCTION()
	void InitializeButton(const FString& InButtonText, EButtonActionType InActionType);

	UFUNCTION()
	void OnButtonClick();
};
