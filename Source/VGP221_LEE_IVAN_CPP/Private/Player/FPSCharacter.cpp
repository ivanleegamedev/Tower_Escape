#include "Player/FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!FPSCameraComponent) {
		
		// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera")); // Equivalent to "Instantiate" in Unity. But only in constructors.
		
		// Attach the camera component to our capsule component.
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		
		// Position the camera slightlyi above the eyes
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		
		// Enable the pawn to control the camera rotation.
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor Called from FPSCharacter"));

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

	// Set up the health component.
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Spawning FPSCharacter")));

	if (UserWidgetClass)
	{
		UserWidget = CreateWidget<UFPSUserWidget>(GetWorld(), UserWidgetClass);
		UserWidget->AddToViewport();
	}

	if (HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &AFPSCharacter::OnHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &AFPSCharacter::OnCharacterDeath);
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "Movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Set up "Look" bindings.
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	// Set up "Action" bindings ie. Jump, Fire
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
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
	// for testing purposes
	TakeDamage_Implementation(10.0f);

	// Rest of the fire code
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Player Fired Pressed")));
	// Attempt to fire a projectile.
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

void AFPSCharacter::TakeDamage_Implementation(float DamageAmount)
{
	if (HealthComponent)
	{
		HealthComponent->ReduceHealth(DamageAmount);
	}

	// Easy way to access the game mode
	//AFPSGamemode* Gamemode = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	//if (HealthComponent)
	//{
	//	HealthComponent->ReduceHealth(10.0f);
	//	float HealthPercent = HealthComponent->CurrentHealth / HealthComponent->MaxHealth;

	//	Gamemode->CurrentWidget->SetHealthBar(HealthPercent);
	//}
}

void AFPSCharacter::HandleDeath_Implementation()
{
	// Disable input
	DisableInput(Cast<APlayerController>(GetController()));
	
	// Call OnCharacterDeath to handle additional death logic to the character
	OnCharacterDeath();
}

void AFPSCharacter::OnHealthChanged(UHealthComponent* HealthComp, float NewHealth)
{
	if (UserWidget)
	{
		float HealthPercent = NewHealth / HealthComponent->MaxHealth;
		UserWidget->SetHealthBar(HealthPercent);
	}
}

void AFPSCharacter::OnCharacterDeath()
{
	// Call Game Over Screen
	UE_LOG(LogTemp, Warning, TEXT("Character has died!"));
}
