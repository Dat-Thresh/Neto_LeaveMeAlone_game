// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;


USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()

//***VALUES*****//

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon DefaultAmmoWeapon{30, 0, true};

	FAmmoWeapon CurrentAmmoWeapon;
	
	DECLARE_MULTICAST_DELEGATE(FOnBulletsOff);
	FOnBulletsOff OnBulletsOff;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	double FireRate = 0.15f;
	

	FTimerHandle FireTimer;

//***METHODS***//
public:	
	// Sets default values for this actor's properties
	ALMABaseWeapon();
	void Fire();
	void DecrementBullets();
	bool IsCurrentClipEmpty() const;
	void ChangeClip();
	void StopFire();
	bool IsCurrentClipFull() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shoot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
