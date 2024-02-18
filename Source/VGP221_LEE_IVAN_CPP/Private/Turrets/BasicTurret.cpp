#include "Turrets/BasicTurret.h"

ABasicTurret::ABasicTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Root);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void ABasicTurret::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr)

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Spawning Turret")));

	HealthComponent->OnHealthChanged.AddDynamic(this, &ABasicTurret::OnHealthChanged);
	HealthComponent->OnDeath.AddDynamic(this, &ABasicTurret::OnTurretDeath);
}

void ABasicTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicTurret::TakeDamage_Implementation(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(DamageAmount);

		// Debug log ensuring the damage is being taken
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("BasicTurret's TakeDamage_Implementation Called")));
	}
}

void ABasicTurret::HandleDeath_Implementation()
{
	OnTurretDeath();
}

void ABasicTurret::OnHealthChanged(float NewHealthPercentage)
{
	// Debug log ensuring the health is being changed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("BasicTurret's OnHealthChanged Called")));
}

void ABasicTurret::OnTurretDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Turret has been destroyed!")));
	Destroy();
}

