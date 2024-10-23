// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/LMADefaultCharacter.h"
#include "Components/SphereComponent.h"
#include "LMA_HealthComponent.h"
#include "LMA_HealthPickup.generated.h"

class USphereComponent;

UCLASS()
class LEAVEMEALONE_API ALMA_HealthPickup : public AActor
{
	GENERATED_BODY()

	/*VALUES*/
protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = 5.0f, ClampMax = 100.0f))
	float HealthFromPickup = 100.0f;
	
		
	/*METHODS*/
private:
	bool GivePickup(ALMADefaultCharacter* Character);
	void PickupWasTaken();
	void RespawnPickup();
public:	
	// Sets default values for this actor's properties
	ALMA_HealthPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
