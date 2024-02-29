#include "Environment/Lava.h"

ALava::ALava()
{
	PrimaryActorTick.bCanEverTick = true;
	
	if (!TriggerVolume)
	{
		TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
		RootComponent = TriggerVolume;
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALava::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ALava::OnOverlapEnd);
	}

	if (!LavaMesh)
	{
		LavaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LavaMesh"));
		LavaMesh->SetupAttachment(GetRootComponent());
	}
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
	// debug on screen for the overlap event
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));

	IIDamageable* DamageableActor = Cast<IIDamageable>(OtherActor);
	if (DamageableActor)
	{
		ActorInLava = DamageableActor;
		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &ALava::ApplyDamage, 2.0f, true, 0.0f);
	}
}

void ALava::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// debug on screen for the overlap event
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));

	if (Cast<IIDamageable>(OtherActor) == ActorInLava)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		ActorInLava = nullptr;
	}
}

void ALava::ApplyDamage()
{
	if (ActorInLava)
	{
		ActorInLava->ReceiveDamage(LavaDamage);
	}
}
