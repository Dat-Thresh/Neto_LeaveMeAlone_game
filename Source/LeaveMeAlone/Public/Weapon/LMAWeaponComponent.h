// LeaveMeAlone Game by Netologiya. All RightsReserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMABaseWeapon.h"
#include "LMA_HealthComponent.h"
#include "Player/LMADefaultCharacter.h"
#include "LMAWeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	//***VALUES***//
public:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage;

	bool AnimReloading = false;

	UPROPERTY();
	ULMA_HealthComponent* HealthComponent;

	//**METHODS***//

public:	
	// Sets default values for this component's properties
	ULMAWeaponComponent();
	void SpawnWeapon();
	void Fire();
	void StopFire();
	void Reload();
	void InitAnimNotify();
	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);
	bool CanReload() const;
	void NewReload();
	void BulletsOff();
	UFUNCTION(BlueprintCallable)
	bool GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
