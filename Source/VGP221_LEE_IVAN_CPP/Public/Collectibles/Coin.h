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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	// Create a static mesh component
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
