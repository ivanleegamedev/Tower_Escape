#include "Environment/Lava.h"

ALava::ALava()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALava::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ALava::OnOverlapEnd);

	LavaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LavaMesh"));
	LavaMesh->SetupAttachment(GetRootComponent());
}

void ALava::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALava::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		ActorInLava = OtherActor;
		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &ALava::ApplyDamage, 2.0f, true, 0.0f);
	}
}

void ALava::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		ActorInLava = nullptr;
	}
}

void ALava::ApplyDamage()
{
	if (ActorInLava)
	{
		UGameplayStatics::ApplyDamage(ActorInLava, DamagePerSecond, nullptr, this, nullptr);
	}
}

