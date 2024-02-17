#pragma once

#include "CoreMinimal.h"
#include "Collectibles/Collectible.h"
#include "Kismet/GameplayStatics.h"
#include "Gamemode/FPSGamemode.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API ACoin : public ACollectible
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Points = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationRate = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollectRotationRate = 1500;

	FTimerHandle DeathTimerHandle;
	void DeathTimerComplete();
};
