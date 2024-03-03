#include "Player/FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!FPSCameraComponent) 
	{		
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));		
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));		
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));		
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor Called from FPSCharacter"));

	if (!FPSMesh)
	{
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		check(FPSMesh != nullptr);
		FPSMesh->SetOnlyOwnerSee(true);
		FPSMesh->SetupAttachment(FPSCameraComponent);
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;

		GetMesh()->SetOwnerNoSee(true);
	}

	if (!HealthComponent)
	{
		HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	}
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Spawning FPSCharacter")));

	HealthComponent->OnHealthChangedEvent.AddDynamic(this, &AFPSCharacter::UpdateHealthUI);
	HealthComponent->OnDeathEvent.AddDynamic(this, &AFPSCharacter::HandleDeath);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AFPSCharacter::PauseGame);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRight(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		//MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Projectile class set for FPSCharacter!"))
	}
}

void AFPSCharacter::PauseGame()
{
	AFPSGamemode* FPSGamemode = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (FPSGamemode)
	{
		FPSGamemode->TogglePauseMenu();
	}
}

void AFPSCharacter::ReceiveDamage(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(DamageAmount);
	}
}

void AFPSCharacter::HandleDeath()
{
	OnCharacterDeath();
}

void AFPSCharacter::UpdateHealthUI(float NewHealthPercentage)
{
	AFPSGamemode* FPSGamemode = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (FPSGamemode && FPSGamemode->CurrentWidget)
	{
		FPSGamemode->CurrentWidget->SetHealthBar(NewHealthPercentage);
	}
}

void AFPSCharacter::OnCharacterDeath()
{
	// Destroy Actor
	Destroy();

	// TODO: Call Game Over Screen
	//DisableInput(Cast<APlayerController>(GetController()));

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Character has died!")));
}

bool AFPSCharacter::IsPlayerDetected_Implementation()
{
	return true;
}
