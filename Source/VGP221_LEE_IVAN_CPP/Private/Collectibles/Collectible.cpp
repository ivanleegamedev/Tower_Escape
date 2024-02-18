#include "Collectibles/Collectible.h"

ACollectible::ACollectible()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::BeginOverlap);
		CollisionComponent->InitSphereRadius(50.0f);
		RootComponent = CollisionComponent;
	}
}

void ACollectible::BeginPlay()
{
	Super::BeginPlay();	
}

void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectible::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnCollect();
}

void ACollectible::OnCollect()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Collectible OnCollect Called")));
}
