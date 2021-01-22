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
}

// Called every frame
void UBR_CombatHandler_Player::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Fire left/right pistol depending on mouse click
void UBR_CombatHandler_Player::Fire(EPistol Pistol)
{	
	FName Socket = "Muzzle_Left";
	if (Pistol == EPistol::RIGHT)
	{
		Socket = "Muzzle_Right";
	}

	// Spawn projectile
	if (!ProjectileClass) {return;}
	FVector SpawnLocation = Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketTransform(Socket).GetLocation(); // Muzzle location
	FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, GetAimPoint());	// Angle from muzzle towards player aim reticle
	ABR_Projectile *ProjectileTemp = GetWorld()->SpawnActor<ABR_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);

	// Spawn VFX and SFX
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Cast<ACharacter>(GetOwner())->GetMesh(), Socket);
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
