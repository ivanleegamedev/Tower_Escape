#include "HealthComponent/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the player's health to the maximum health
	CurrentHealth = MaxHealth;	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::ReduceHealth(float DamageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(this, CurrentHealth);

	// Check for death
	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

