// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LevelActors/Pickup/LMA_HealthPickup.h"

// Sets default values
ALMA_HealthPickup::ALMA_HealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);

}

// Called when the game starts or when spawned
void ALMA_HealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMA_HealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALMA_HealthPickup::PickupWasTaken()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALMA_HealthPickup::RespawnPickup,
		RespawnTime);
}

void ALMA_HealthPickup::RespawnPickup()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);
}

bool ALMA_HealthPickup::GivePickup(ALMADefaultCharacter* Character)
{
	const auto HealthComponent = Character->GetHealthComponent();
	if (!HealthComponent) return false;
	return HealthComponent->AddHealth(HealthFromPickup);
}

void ALMA_HealthPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Character = Cast<ALMADefaultCharacter>(OtherActor);
	if (GivePickup(Character))
	{
		PickupWasTaken();
	}
}