#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageable.generated.h"

UINTERFACE(MinimalAPI)
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

public:
	UFUNCTION()
	virtual void ReceiveDamage(float DamageAmount) = 0;
	UFUNCTION()
	virtual void HandleDeath() = 0;
};
