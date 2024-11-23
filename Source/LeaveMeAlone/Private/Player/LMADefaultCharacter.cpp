// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LMA_HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/LMAWeaponComponent.h"




// Sets default values
ALMADefaultCharacter::ALMADefaultCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	HealthComponent = CreateDefaultSubobject<ULMA_HealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ALMADefaultCharacter::OnDeath);

	WeaponComponent = CreateDefaultSubobject<ULMAWeaponComponent>("Weapon");

}

// Called when the game starts or when spawned
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize,
			FVector(0));
	}
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnHealthChanged.AddUObject(this, &ALMADefaultCharacter::OnHealthChanged);
	
}

// Called every frame
void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Stamina = %f"), Endurance));
	if (!(HealthComponent->IsDead()))
	{
		RotationPlayerOnCursor();
		CheckSprintPossibility();	
	}
}

// Called to bind functionality to input
void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALMADefaultCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ALMADefaultCharacter::CameraZoom);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ALMADefaultCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ALMADefaultCharacter::SprintStop);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &ULMAWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &ULMAWeaponComponent::Reload);
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::CameraZoom(float Value)
{
	if ((SpringArmComponent->TargetArmLength >= MinCameraZoom && Value > 0 && SpringArmComponent->TargetArmLength <= MaxCameraZoom - 100)
		|| (SpringArmComponent->TargetArmLength <= MaxCameraZoom && Value < 0 && SpringArmComponent->TargetArmLength >= MinCameraZoom + 100)) {
		SpringArmComponent->TargetArmLength += Value;
	}
	
}

void ALMADefaultCharacter::OnDeath()
{
	WeaponComponent->StopFire();
	CurrentCursor->DestroyRenderState_Concurrent();
	PlayAnimMontage(DeathMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ALMADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
			ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}
	}
}

void ALMADefaultCharacter::OnHealthChanged(float NewHealth)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health = %f"), NewHealth));
}


void ALMADefaultCharacter::SprintStart()
{
	
	if (Endurance > 0) {
		isOnSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	
}

void ALMADefaultCharacter::SprintStop()
{
	isOnSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ALMADefaultCharacter::CheckSprintPossibility(){
		if (!isOnSprint) {
			if (Endurance < MaxEndurance) {
				//Endurance += RecoveryEnduranceByTick;
				Endurance = FMath::Clamp(Endurance + RecoveryEnduranceByTick, 0.0f, MaxEndurance);
			}
		}
		else {
			if (Endurance > 0) {
				//Endurance -= LooseEnduranceByTick;
				Endurance = FMath::Clamp(Endurance - LooseEnduranceByTick, 0.0f, MaxEndurance);
			}
		}
		if (Endurance <= 0) {
			SprintStop();
		}
}


	