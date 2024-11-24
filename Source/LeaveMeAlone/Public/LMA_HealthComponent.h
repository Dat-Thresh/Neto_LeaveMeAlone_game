// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMA_HealthComponent.generated.h"

class ULMA_HealthComponent;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMA_HealthComponent : public UActorComponent
{
	GENERATED_BODY()
	/*VALUES*/
private:
	float Health = 0.0f;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	/*METHODS*/
public:	
	// Sets default values for this component's properties
	ULMA_HealthComponent();
	

	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	DECLARE_MULTICAST_DELEGATE(FOnDeath);
	FOnDeath OnDeath;

	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);
	FOnHealthChanged OnHealthChanged;


	bool AddHealth(float NewHealth);
	bool IsHealthFull() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


		
};
