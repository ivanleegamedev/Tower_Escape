#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedEvent, float, NewHealthPercentage);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VGP221_LEE_IVAN_CPP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;

private:
	float CurrentHealth;

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void IncreaseHealth(float Amount);

	// Delegate for when health changes
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedEvent OnHealthChangedEvent;

	// Delegate for when health reaches 0
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathEvent OnDeathEvent;
};
