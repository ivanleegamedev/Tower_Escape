#include "Collectibles/Coin.h"

ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

	UE_LOG(LogTemp, Warning, TEXT("Coin OnCollect Called"));

	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACoin::DeathTimerComplete, 0.5f, false);

	RotationRate = CollectRotationRate;
}

void ACoin::DeathTimerComplete()
{
	// Easy way to acccess the gamemode
	AFPSGamemode* Gamemode = Cast<AFPSGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode)
	{
		Gamemode->CurrentWidget->SetScore(Points);
	}

	Destroy();
}
