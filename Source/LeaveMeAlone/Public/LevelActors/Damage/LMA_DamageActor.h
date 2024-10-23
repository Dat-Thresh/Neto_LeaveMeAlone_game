// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "LMA_DamageActor.generated.h"

//class USphereComponent;
//class UStaticMeshComponent;

UCLASS()
class LEAVEMEALONE_API ALMA_DamageActor : public AActor
{
	GENERATED_BODY()

public:
	/*VALUES*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float SphereRadius = 100.0f;

		/*METHODS*/

public:
	// Sets default values for this actor's properties
	ALMA_DamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
