#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent/HealthComponent.h"
#include "Interfaces/IDamageable.h"
#include "Interfaces/ITurretAnimation.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "BasicTurret.generated.h"

UCLASS()
class VGP221_LEE_IVAN_CPP_API ABasicTurret : public AActor, public IIDamageable, public IITurretAnimation
{
	GENERATED_BODY()
	
public:	
	ABasicTurret();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Beam;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BeamStartLocation;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BeamEndLocation;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BeamTarget;

	UPROPERTY()
	FTimerHandle BeamTimerHandler;

	int BeamCounter = 0;
	FRotator LookAtRotation;
	FRotator TargetRotation;
	FRotator RotationDelta;

	UPROPERTY(EditAnywhere)
	float ChangeTargetDelay = 5.0f;

	UPROPERTY(EditAnywhere)
	float RotationRateMultiplier = 1.0f;

	UFUNCTION()
	void UpdateLookAtTarget(float DeltaTime);

	UFUNCTION()
	void BeamScanning();

private:
	// IDamageable interface implementation
	void TakeDamage_Implementation(float DamageAmount) override;
	void HandleDeath_Implementation() override;

	UFUNCTION()
	void OnTurretDeath();
};
