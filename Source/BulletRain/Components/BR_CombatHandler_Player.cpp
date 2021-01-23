#include "BR_CombatHandler_Player.h"
#include "BulletRain/Actors/BR_Projectile.h"
#include "Components/SceneComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"



#include "DrawDebugHelpers.h"

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
	
	AmmoLeft = MaxMagAmmo, AmmoRight = MaxMagAmmo;
}

// Called every frame
void UBR_CombatHandler_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Fire left/right pistol depending on mouse click
void UBR_CombatHandler_Player::Fire(EPistol Pistol)
{	
	FName Socket;
	if (Pistol == EPistol::RIGHT)
	{
		if (AmmoRight == 0) return;
		Socket = "Muzzle_Right";
		AmmoRight--;
	}
	if (Pistol == EPistol::LEFT)
	{
		if (AmmoLeft == 0) return;
		Socket = "Muzzle_Left";
		AmmoLeft--;
	}

	// Spawn projectile
	if (!ProjectileClass) {return;}
	FVector SpawnLocation = Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketTransform(Socket).GetLocation(); // Muzzle location
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, GetAimPoint());	// Angle from muzzle towards player aim reticle
	ABR_Projectile *ProjectileTemp = GetWorld()->SpawnActor<ABR_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

	// Spawn VFX and SFX
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Cast<ACharacter>(GetOwner())->GetMesh(), Socket, FVector(0.f), FRotator(0.f), FVector(0.5f));
}

// Reload left/right pistol
void UBR_CombatHandler_Player::Reload(EPistol Pistol) 
{
	if (Pistol == EPistol::RIGHT)
	{
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
}

int UBR_CombatHandler_Player::GetCarriedAmmo() const
{
	return CurrentCarriedAmmo;
}

// Get te current ammo remaining for left/right pistol
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
void UBR_CombatHandler_Player::SetAmmoCapacity(int Capacity) 
{
	MaxCarriedAmmo = Capacity;
}

void UBR_CombatHandler_Player::SetMagCapacity(int Capacity) 
{
	MaxMagAmmo = Capacity;
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

	FVector LineTraceEnd = PlayerViewpointLocation + FVector(PlayerViewpointRotation.Vector() * Range);

	return LineTraceEnd;
}
