#pragma once

#include "CoreMinimal.h"
#include "Collectibles/Collectible.h"
#include "Kismet/GameplayStatics.h"
#include "HealthPack.generated.h"

/**
 * 
 */
UCLASS()
class VGP221_LEE_IVAN_CPP_API AHealthPack : public ACollectible
{
	GENERATED_BODY()
	
public:
	AHealthPack();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HealthPackMesh;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float HealthAmount = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationRate = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollectRotationRate = 1500;

	FTimerHandle DeathTimerHandle;
	void DeathTimerComplete();
};
