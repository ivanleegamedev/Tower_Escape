#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthComponent/HealthComponent.h"
#include "Interfaces/IDamageable.h"
#include "BasicTurret.generated.h"

UCLASS()
class VGP221_LEE_IVAN_CPP_API ABasicTurret : public AActor, public IIDamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* TurretMesh;

private:
	// IDamageable interface implementation
	void TakeDamage_Implementation(float DamageAmount) override;
	void HandleDeath_Implementation() override;

	UFUNCTION()
	void OnHealthChanged(float NewHealthPercentage);

	UFUNCTION()
	void OnTurretDeath();
};
