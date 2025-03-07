#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	// This will be drawn at the center of the screen.
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

public:

	// Primary draw call for the HUD.
	virtual void DrawHUD() override;
};
