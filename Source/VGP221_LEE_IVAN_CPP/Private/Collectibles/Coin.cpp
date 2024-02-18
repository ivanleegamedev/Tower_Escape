#include "Collectibles/Coin.h"

ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!CoinMesh)
	{
		CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
		CoinMesh->SetupAttachment(CollisionComponent);
	}
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

void ACoin::OnCollect()
{
	Super::OnCollect();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Coin OnCollect Called")));

	AFPSGamemode* Gamemode = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode)
	{
		Gamemode->CurrentWidget->SetScore(Points);
	}

	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACoin::DeathTimerComplete, 0.5f, false);

	RotationRate = CollectRotationRate;
}

void ACoin::DeathTimerComplete()
{
	Destroy();
}
