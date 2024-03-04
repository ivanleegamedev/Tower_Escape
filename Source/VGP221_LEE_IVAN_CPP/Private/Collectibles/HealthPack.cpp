#include "Collectibles/HealthPack.h"
#include "Player/FPSCharacter.h"
#include "HealthComponent/HealthComponent.h"

AHealthPack::AHealthPack()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!HealthPackMesh)
	{
		HealthPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealthPackMesh"));
		HealthPackMesh->SetupAttachment(CollisionComponent);
	}
}

void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
}

void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

void AHealthPack::OnCollect()
{
	Super::OnCollect();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("HealthPack OnCollect Called")));

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter && PlayerCharacter->HealthComponent)
	{
		PlayerCharacter->HealthComponent->IncreaseHealth(HealthAmount);
	}

	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AHealthPack::DeathTimerComplete, 0.5f, false);

	RotationRate = CollectRotationRate;
}

void AHealthPack::DeathTimerComplete()
{
	Destroy();
}
