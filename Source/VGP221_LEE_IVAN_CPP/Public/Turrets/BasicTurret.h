#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent/HealthComponent.h"
#include "Interfaces/IDamageable.h"
#include "Interfaces/ITurretAnimation.h"
#include "Interfaces/IDetectable.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "BasicTurret.generated.h"

UCLASS()
class VGP221_LEE_IVAN_CPP_API ABasicTurret : public AActor, public IIDamageable, public IITurretAnimation
{
	GENERATED_BODY()
	
public:	
	ABasicTurret();

protected:
	virtual void BeginPlay() override;

	// Beam Length
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Beam")
	float BeamLength = 1000.0f;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Beam;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BeamScanTarget1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BeamScanTarget2;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BeamTarget;

	UPROPERTY()
	FTimerHandle ScanTimerHandler;

	UPROPERTY()
	FTimerHandle TraceTimerHandler;

	int BeamCounter = 0;
	FRotator LookAtRotation;
	FRotator TargetRotation;
	FRotator RotationDelta;

	UPROPERTY(EditAnywhere)
	float ChangeTargetDelay = 5.0f;

	UPROPERTY(EditAnywhere)
	float RotationRateMultiplier = 1.0f;

	UPROPERTY()
	AActor* Player = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* P_MuzzleFlash;

	UFUNCTION()
	void UpdateLookAtTarget(float DeltaTime);

	UFUNCTION()
	void BeamScanTarget();

	UFUNCTION(BlueprintCallable)
	void SetBeamLength(float Length);

	UFUNCTION()
	void TraceBeam();

	UFUNCTION()
	void CheckPlayerInSight(AActor* HitActor);

	UFUNCTION()
	void FollowPlayer(float DeltaTime);

	UFUNCTION()
	void Shoot();

	// IDamageable interface implementation
	void TakeDamage_Implementation(float DamageAmount) override;
	void HandleDeath_Implementation() override;

	UFUNCTION()
	void OnTurretDeath();
};
