#include "HealthComponent/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;	
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth / MaxHealth);

	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::IncreaseHealth(float Amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth / MaxHealth);
}