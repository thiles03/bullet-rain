#include "BR_CombatHandler_Player.h"
#include "BulletRain/Actors/BR_Projectile.h"
#include "BulletRain/Actors/BR_Grenade.h"
#include "Components/SceneComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Constructor
UBR_CombatHandler_Player::UBR_CombatHandler_Player()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

// Called when the game starts
void UBR_CombatHandler_Player::BeginPlay()
{
	Super::BeginPlay();
	PlayerMesh = Cast<ACharacter>(GetOwner())->GetMesh();
	AmmoLeft = MaxMagAmmo, AmmoRight = MaxMagAmmo, CurrentGrenades = MaxGrenades;
	ReloadDelegateLeft = FTimerDelegate::CreateUObject(this, &UBR_CombatHandler_Player::SetIsReloading, EPistol::LEFT, false);
	ReloadDelegateRight = FTimerDelegate::CreateUObject(this, &UBR_CombatHandler_Player::SetIsReloading, EPistol::RIGHT, false);
}

// Called every frame
void UBR_CombatHandler_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Get the current ammo carried on the player
int UBR_CombatHandler_Player::GetCarriedAmmo() const
{
	return CurrentCarriedAmmo;
}

int UBR_CombatHandler_Player::GetCurrentGrenades() const
{
	return CurrentGrenades;
}

// Return true if player is reloading
bool UBR_CombatHandler_Player::GetIsReloading() const 
{
	return (IsReloadingLeft && IsReloadingRight);
}

// Return true if attacking with right pistol
bool UBR_CombatHandler_Player::GetIsAttackingRight() const 
{
	return IsAttackingRight;
}

// Return true if attacking with left pistol
bool UBR_CombatHandler_Player::GetIsAttackingLeft() const 
{
	return IsAttackingLeft;
}

// Get the current ammo remaining for left/right pistol
int UBR_CombatHandler_Player::GetWeaponAmmo(EPistol Pistol) const
{
	if (Pistol == EPistol::RIGHT)
	{
		return AmmoRight;
	}
	if (Pistol == EPistol::LEFT)
	{
		return AmmoLeft;
	}
	return 0;
}

// Set the maximum ammo carrying capacity
void UBR_CombatHandler_Player::SetMaxCarriedAmmo(int Capacity) 
{
	MaxCarriedAmmo = Capacity;
}

// Set the current ammo carried on the player
void UBR_CombatHandler_Player::SetCurrentCarriedAmmo(int Amount) 
{
	CurrentCarriedAmmo = FMath::Clamp((CurrentCarriedAmmo + Amount), 0, MaxCarriedAmmo);
}

void UBR_CombatHandler_Player::SetCurrentGrenades(int Amount) 
{
	CurrentGrenades += FMath::Clamp((CurrentGrenades + Amount), 0, MaxGrenades);
}

void UBR_CombatHandler_Player::SetMaxGrenades(int Amount) 
{
	MaxGrenades = Amount;
}

// Set the maximum magazine size
void UBR_CombatHandler_Player::SetMaxMagAmmo(int Capacity) 
{
	MaxMagAmmo = Capacity;
}

// Set IsReloading
void UBR_CombatHandler_Player::SetIsReloading(EPistol Pistol, bool Reloading) 
{
	if(Pistol == EPistol::LEFT) IsReloadingLeft = Reloading;
	if(Pistol == EPistol::RIGHT) IsReloadingRight = Reloading;
}

void UBR_CombatHandler_Player::SetIsAttackingRight(bool Attacking) 
{
	IsAttackingRight = Attacking;
}

void UBR_CombatHandler_Player::SetIsAttackingLeft(bool Attacking) 
{
	IsAttackingLeft = Attacking;
}

// Fire left/right pistol depending on mouse click
void UBR_CombatHandler_Player::Fire(EPistol Pistol)
{	
	FName Socket;
	if (Pistol == EPistol::RIGHT)
	{
		if (IsReloadingRight || IsAttackingRight) return;
		if(AmmoRight == 0)
		{
			UGameplayStatics::SpawnSoundAttached(EmptyClick, PlayerMesh, Socket);
			return;
		}
		Socket = "Muzzle_Right";
		IsAttackingRight = true;
		AmmoRight--;
	}
	if (Pistol == EPistol::LEFT)
	{
		if (IsReloadingLeft || IsAttackingLeft) return;
		if (AmmoLeft == 0)
		{
			UGameplayStatics::SpawnSoundAttached(EmptyClick, PlayerMesh, Socket);
			return;
		}
		Socket = "Muzzle_Left";
		IsAttackingLeft = true;
		AmmoLeft--;
	}

	// Spawn projectile
	if (!ProjectileClass) {return;}
	FVector SpawnLocation = PlayerMesh->GetSocketTransform(Socket).GetLocation(); // Muzzle location
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, GetAimPoint());	// Angle from muzzle towards player aim reticle
	ABR_Projectile *ProjectileTemp = GetWorld()->SpawnActor<ABR_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

	// Spawn VFX and SFX
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, PlayerMesh, Socket, FVector(0.f), FRotator(0.f), FVector(0.5f));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, PlayerMesh, Socket);
	UGameplayStatics::SpawnSoundAttached(BulletSound, PlayerMesh, Socket);
}

// Reload left/right pistol
void UBR_CombatHandler_Player::Reload(EPistol Pistol) 
{
	if (Pistol == EPistol::RIGHT)
	{
		if(AmmoRight == MaxMagAmmo) return;
		GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerRight, ReloadDelegateRight, ReloadSpeed, false);
		UGameplayStatics::SpawnSoundAttached(ReloadSound, PlayerMesh, "Muzzle_Right");
		if (CurrentCarriedAmmo > (MaxMagAmmo - AmmoRight))
		{
			CurrentCarriedAmmo -= (MaxMagAmmo - AmmoRight);
			AmmoRight = MaxMagAmmo;
		}
		else
		{
			AmmoRight += CurrentCarriedAmmo;
			CurrentCarriedAmmo = 0;
		}
	}
	if (Pistol == EPistol::LEFT)
	{
		if(AmmoLeft == MaxMagAmmo) return;
		GetOwner()->GetWorldTimerManager().SetTimer(ReloadTimerLeft, ReloadDelegateLeft, ReloadSpeed, false);
		UGameplayStatics::SpawnSoundAttached(ReloadSound, PlayerMesh, "Muzzle_Left");
		if (CurrentCarriedAmmo > (MaxMagAmmo - AmmoLeft))
		{
			CurrentCarriedAmmo -= (MaxMagAmmo - AmmoLeft);
			AmmoLeft = MaxMagAmmo;
		}
		else
		{
			AmmoLeft += CurrentCarriedAmmo;
			CurrentCarriedAmmo = 0;
		}
	}
	SetIsReloading(Pistol, true);
}

void UBR_CombatHandler_Player::ThrowGrenade() 
{
	if(CurrentGrenades == 0) return;
	
	// Spawn grenade
	if (!GrenadeClass) {return;}
	FVector RotatedOffest = GetWorld()->GetFirstPlayerController()->GetControlRotation().RotateVector(GrenadeOffset);
	FVector SpawnLocation = (GetOwner()->GetActorLocation()) + RotatedOffest;
	ABR_Grenade *GrenadeTemp = GetWorld()->SpawnActor<ABR_Grenade>(GrenadeClass, SpawnLocation, GetOwner()->GetActorRotation());
	//CurrentGrenades--;
}

// Returns the point under the crosshair that is equals to the range distance from the player
FVector UBR_CombatHandler_Player::GetAimPoint() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceEnd = PlayerViewpointLocation + FVector(PlayerViewpointRotation.Vector() * AttackRange);

	return LineTraceEnd;
}
