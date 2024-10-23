// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMA_HealthComponent.h"

// Sets default values for this component's properties
ULMA_HealthComponent::ULMA_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULMA_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	AActor* OwnerComponent = GetOwner();
	if (OwnerComponent)
	{
		OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &ULMA_HealthComponent::OnTakeAnyDamage);
	}
}

void ULMA_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

bool ULMA_HealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

bool ULMA_HealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool ULMA_HealthComponent::AddHealth(float NewHealth)
{
	if (IsDead() || IsHealthFull()) return false;
	Health = FMath::Clamp(Health + NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	return true;
}
