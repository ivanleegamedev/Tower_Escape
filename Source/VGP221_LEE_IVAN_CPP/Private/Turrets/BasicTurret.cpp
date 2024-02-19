#include "Turrets/BasicTurret.h"

ABasicTurret::ABasicTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Root);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RadarBeam"));
	Beam->SetupAttachment(TurretMesh, TEXT("BeamSocket"));

	BeamStartLocation = CreateDefaultSubobject<USceneComponent>(TEXT("BeamStartLocation"));
	BeamStartLocation->SetupAttachment(Root);

	BeamEndLocation = CreateDefaultSubobject<USceneComponent>(TEXT("BeamEndLocation"));
	BeamEndLocation->SetupAttachment(Root);

	BeamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("BeamTarget"));
	BeamTarget->SetupAttachment(Root);
}

void ABasicTurret::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr)

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Spawning Turret")));

	HealthComponent->OnDeathEvent.AddDynamic(this, &ABasicTurret::OnTurretDeath);

	GetWorldTimerManager().SetTimer(BeamTimerHandler, this, &ABasicTurret::BeamScanning, ChangeTargetDelay, true, 1.0f);
}

void ABasicTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLookAtTarget(DeltaTime);
}

void ABasicTurret::UpdateLookAtTarget(float DeltaTime)
{
	if (LookAtRotation.Equals(TargetRotation, 1.0f))
	{
		return;
	}

	LookAtRotation += RotationDelta * RotationRateMultiplier * DeltaTime;

	if (TurretMesh->GetAnimInstance()->Implements<UITurretAnimation>())
	{
		IITurretAnimation::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
	}
}

void ABasicTurret::BeamScanning()
{
	BeamCounter++;
	
	if (BeamCounter % 2 == 0)
	{
		BeamTarget->SetWorldLocation(BeamStartLocation->GetComponentLocation());
	}
	else
	{
		BeamTarget->SetWorldLocation(BeamEndLocation->GetComponentLocation());
	}

	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = BeamTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
}

void ABasicTurret::TakeDamage_Implementation(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(DamageAmount);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("BasicTurret's OnHealthChanged Called")));
	}
}

void ABasicTurret::HandleDeath_Implementation()
{
	OnTurretDeath();
}

void ABasicTurret::OnTurretDeath()
{
	// Debug message to show that the turret has been destroyed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Turret has been destroyed!")));

	// TODO: Update UI to increase turret destroyed count

	Destroy();
}

