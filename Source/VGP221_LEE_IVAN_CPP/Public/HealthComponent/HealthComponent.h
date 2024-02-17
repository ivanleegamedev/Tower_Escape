#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// Delcare a delegate type for death notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

// Delcare a delegate type for health changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, UHealthComponent*, HealthComponent, float, NewHealth);

UCLASS(Blueprintable)
class VGP221_LEE_IVAN_CPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Tracks the maximum health of the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	// Tracks the current health of the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	// Function to handle the damage taken
	UFUNCTION()
	void ReduceHealth(float DamageAmount);

	// Delegate for when health changes
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	// Delegate for when health reaches 0
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;
};
