#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GUI/ButtonWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameOverText; // Make sure that "GameOverText" name matches the name of the Text in the Widget

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ButtonContainer; // Make sure that "ButtonContainer" name matches the name of the VerticalBox in the Widget

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UButtonWidget> ButtonWidgetPrefab;
};
