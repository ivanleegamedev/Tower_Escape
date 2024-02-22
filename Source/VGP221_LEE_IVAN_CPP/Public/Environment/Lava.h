#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Player/FPSCharacter.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/IDamageable.h"
#include "Lava.generated.h"

UCLASS()
class VGP221_LEE_IVAN_CPP_API ALava : public AActor
{
	GENERATED_BODY()
	
public:	
	ALava();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Colllider for the lava
	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LavaMesh;

	// Damage per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LavaDamage = 10.0f;

	// Function to handle the overlap event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle DamageTimerHandle;
	IIDamageable* ActorInLava = nullptr;

	UFUNCTION()
	void ApplyDamage();
};
