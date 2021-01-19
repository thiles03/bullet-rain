#include "BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CombatHandler_Player.h"
#include "Kismet/KismetMathLibrary.h"

//Constructor
ABR_CharacterPlayer::ABR_CharacterPlayer() 
{
    PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.

	CombatHandler = CreateDefaultSubobject<UBR_CombatHandler_Player>(TEXT("Combat Handler"));
}

//Called every frame
void ABR_CharacterPlayer::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void ABR_CharacterPlayer::BeginPlay() 
{
    Super::BeginPlay();
}

// Called to bind functionality to input
void ABR_CharacterPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABR_CharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABR_CharacterPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABR_CharacterPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookRightRate", this, &ABR_CharacterPlayer::LookRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Combat
	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const EPistol);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("FireRight", IE_Pressed, this, &ABR_CharacterPlayer::Fire, EPistol::RIGHT);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("FireLeft", IE_Pressed, this, &ABR_CharacterPlayer::Fire, EPistol::LEFT);
}

void ABR_CharacterPlayer::LookRight(float AxisValue) 
{
    AddControllerYawInput(RotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

void ABR_CharacterPlayer::LookUp(float AxisValue) 
{
    AddControllerPitchInput(RotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

void ABR_CharacterPlayer::MoveForward(float AxisValue) 
{
    FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

void ABR_CharacterPlayer::MoveRight(float AxisValue) 
{
    FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

void ABR_CharacterPlayer::Fire(EPistol Pistol) 
{
	if (Pistol == EPistol::LEFT) {CombatHandler->Fire(EPistol::LEFT);}
	if (Pistol == EPistol::RIGHT) {CombatHandler->Fire(EPistol::RIGHT);}
}

