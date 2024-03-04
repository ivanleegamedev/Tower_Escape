#include "Turrets/BasicTurret.h"

#define OUT

ABasicTurret::ABasicTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!Root)
	{
		Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
		SetRootComponent(Root);
	}

	if (!TurretMesh)
	{
		TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
		TurretMesh->SetupAttachment(Root);
	}

	if (!HealthComponent)
	{
		HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	}

	if (!Beam)
	{
		Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RadarBeam"));
		Beam->SetupAttachment(TurretMesh, TEXT("BeamSocket"));
	}

	if (!BeamScanTarget1)
	{
		BeamScanTarget1 = CreateDefaultSubobject<USceneComponent>(TEXT("BeamScanTarget1"));
		BeamScanTarget1->SetupAttachment(Root);
	}

	if (!BeamScanTarget2)
	{
		BeamScanTarget2 = CreateDefaultSubobject<USceneComponent>(TEXT("BeamScanTarget2"));
		BeamScanTarget2->SetupAttachment(Root);
	}

	if (!BeamTarget)
	{
		BeamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("BeamTarget"));
		BeamTarget->SetupAttachment(Root);
	}

	SetBeamLength(BeamLength);

	if (!P_MuzzleFlash)
	{
		P_MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MuzzleFlash"));
		P_MuzzleFlash->SetupAttachment(TurretMesh, TEXT("BeamSocket"));
		P_MuzzleFlash->SetAutoActivate(false);
	}
}

void ABasicTurret::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr)

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Spawning Turret")));

	HealthComponent->OnDeathEvent.AddDynamic(this, &ABasicTurret::OnTurretDeath);

	GetWorldTimerManager().SetTimer(ScanTimerHandler, this, &ABasicTurret::BeamScanTarget, ChangeTargetDelay, true, 1.0f);
	GetWorldTimerManager().SetTimer(TraceTimerHandler, this, &ABasicTurret::TraceBeam, 0.1f, true, 0.1f);
}

void ABasicTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player)
	{
		FollowPlayer(DeltaTime);
	}
	else
	{
		UpdateLookAtTarget(DeltaTime);
	}
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

void ABasicTurret::BeamScanTarget()
{
	BeamCounter++;
	
	if (BeamCounter % 2 == 0)
	{
		BeamTarget->SetWorldLocation(BeamScanTarget1->GetComponentLocation());
	}
	else
	{
		BeamTarget->SetWorldLocation(BeamScanTarget2->GetComponentLocation());
	}

	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = BeamTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
}

void ABasicTurret::SetBeamLength(float Length)
{
	Beam->SetRelativeScale3D(FVector(Length / 400, Beam->GetRelativeScale3D().Y, Beam->GetRelativeScale3D().Z));
	Beam->SetRelativeLocation(FVector(Length / (-8), 0, 0));
}

void ABasicTurret::TraceBeam()
{
	FHitResult HitResult;
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = Start + Beam->GetForwardVector() * BeamLength;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Camera, CollisionQueryParams);

	if (bHit)
	{
		// Adjust Beam Length
		SetBeamLength(HitResult.Distance);

		CheckPlayerInSight(HitResult.GetActor());
	}
	else
	{
		// Reset Beam Length
		SetBeamLength(BeamLength);
	}
}

void ABasicTurret::CheckPlayerInSight(AActor* HitActor)
{
	if (HitActor->Implements<UIDetectable>())
	{
		bool bIsPlayer = IIDetectable::Execute_IsPlayerDetected(HitActor);
		if (bIsPlayer)
		{
			if (!Player)
			{
				Player = HitActor;

				// Start Shooting
				GetWorldTimerManager().SetTimer(ShootTimerHandler, this, &ABasicTurret::Shoot, 0.75f, true, 0.1f);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("BasicTurret Has Player In Sight")));
			}
		}		
	}
	else if (Player)
	{
		Player = nullptr;
		// Stop Shooting
		GetWorldTimerManager().ClearTimer(ShootTimerHandler);
	}
	
}

void ABasicTurret::FollowPlayer(float DeltaTime)
{
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = Player->GetActorLocation();

	FRotator RotationToPlayer = UKismetMathLibrary::FindLookAtRotation(Start, End);

	LookAtRotation = FMath::RInterpTo(LookAtRotation, RotationToPlayer, DeltaTime, 100.0f);

	if (TurretMesh->GetAnimInstance()->Implements<UITurretAnimation>())
	{
		IITurretAnimation::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
	}
}

void ABasicTurret::Shoot()
{
	// Play Sound at location
	UGameplayStatics::PlaySoundAtLocation(this, S_ShootSound, P_MuzzleFlash->GetComponentLocation());

	// Play Muzzle Flash
	P_MuzzleFlash->Activate(true);

	FHitResult HitResult;
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = Start + Beam->GetForwardVector() * BeamLength;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Camera, CollisionQueryParams);

	if (bHit && HitResult.GetActor())
	{
		IIDamageable* DamageableActor = Cast<IIDamageable>(HitResult.GetActor());
		if (DamageableActor)
		{
			// Use the interface method to apply damage
			DamageableActor->ReceiveDamage(TurretDamageAmount);
		}
	}
}

void ABasicTurret::ReceiveDamage(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(DamageAmount);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("BasicTurret's OnHealthChanged Called")));
	}
}

void ABasicTurret::HandleDeath()
{
	OnTurretDeath();
}

void ABasicTurret::OnTurretDeath()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Turret has been destroyed!")));

	AFPSGamemode* GM = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->TurretDestroyed();
	}

	// Assuming SetScore is a method within UFPSUserWidget
	if (UFPSUserWidget* HUDWidget = Cast<UFPSUserWidget>(GM->CurrentWidget))
	{
		HUDWidget->SetScore(ScoreCount);
	}

	Destroy();
}

