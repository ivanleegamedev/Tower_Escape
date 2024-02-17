#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UIDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VGP221_LEE_IVAN_CPP_API IIDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// The standard way to take damage
	UFUNCTION(BlueprintNativeEvent, Category = "Damage") // BlueprintNativeEvent means that the function will be implemented in C++ and can be overridden in Blueprints
	void TakeDamage(float DamageAmount);

	// An event for handling death
	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void HandleDeath();
};
