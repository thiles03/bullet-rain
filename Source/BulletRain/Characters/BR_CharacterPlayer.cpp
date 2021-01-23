#include "BR_CharacterPlayer.h"
#include "BulletRain/Components/BR_CombatHandler_Player.h"
#include "BulletRain/Components/BR_CharacterStats_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Constructor
ABR_CharacterPlayer::ABR_CharacterPlayer() 
{
    PrimaryActorTick.bCanEverTick = true; // Set this character to call Tick() every frame.

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CombatHandler = CreateDefaultSubobject<UBR_CombatHandler_Player>(TEXT("Combat Handler"));
	PlayerStats = CreateDefaultSubobject<UBR_CharacterStats_Player>(TEXT("Player Stats"));

	Camera->SetupAttachment(GetMesh(), TEXT("spine_02"));
}

// Called every frame
void ABR_CharacterPlayer::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
	FOVTimeline.TickTimeline(DeltaTime);
}

// Called when the game starts or when spawned
void ABR_CharacterPlayer::BeginPlay() 
{
    Super::BeginPlay();

	if (fCurve) {SetupTimeline();}
}

// Called to bind functionality to input
void ABR_CharacterPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABR_CharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABR_CharacterPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ABR_CharacterPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABR_CharacterPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookRightRate", this, &ABR_CharacterPlayer::LookRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ABR_CharacterPlayer::ToggleCrouch);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABR_CharacterPlayer::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABR_CharacterPlayer::SprintReset);

	// Combat
	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const EPistol);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("FireRight", IE_Pressed, this, &ABR_CharacterPlayer::Fire, EPistol::RIGHT);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("FireLeft", IE_Pressed, this, &ABR_CharacterPlayer::Fire, EPistol::LEFT);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ReloadRight", IE_Pressed, this, &ABR_CharacterPlayer::Reload, EPistol::RIGHT);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ReloadLeft", IE_Pressed, this, &ABR_CharacterPlayer::Reload, EPistol::LEFT);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ABR_CharacterPlayer::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ABR_CharacterPlayer::AimReset);
	PlayerInputComponent->BindAction("BulletTime", IE_Pressed, this, &ABR_CharacterPlayer::BulletTime);
}

bool ABR_CharacterPlayer::GetIsSprinting() const
{
	return IsSprinting;
}

// Aim weapon
void ABR_CharacterPlayer::Aim()
{
	IsAiming = true;
	ABR_CharacterBase::SetSpeed(AimMoveSpeed);
	FOVTimeline.Play();
	CurrentRotationRate = AimRotationRate;
	TurnDampening = .4f;
}


// Stop aiming
void ABR_CharacterPlayer::AimReset()
{
	IsAiming = false;
	ABR_CharacterBase::SetSpeed(MaxSpeed);
	FOVTimeline.Reverse();
	CurrentRotationRate = BaseRotationRate;
	TurnDampening = 1.f;
}

// Call to CombatHandler to fire pistols
void ABR_CharacterPlayer::Fire(EPistol Pistol) 
{
	if (IsSprinting) return;
	if (Pistol == EPistol::LEFT) {CombatHandler->Fire(EPistol::LEFT);}
	if (Pistol == EPistol::RIGHT) {CombatHandler->Fire(EPistol::RIGHT);}
}

void ABR_CharacterPlayer::Reload(EPistol Pistol) 
{
	if (Pistol == EPistol::LEFT) {CombatHandler->Reload(EPistol::LEFT);}
	if (Pistol == EPistol::RIGHT) {CombatHandler->Reload(EPistol::RIGHT);}
}

// Look right/left using gamepad
void ABR_CharacterPlayer::LookRight(float AxisValue) 
{
    AddControllerYawInput(CurrentRotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

// Look up/down using gamepad
void ABR_CharacterPlayer::LookUp(float AxisValue) 
{
    AddControllerPitchInput(CurrentRotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

// Move forward/backwards
void ABR_CharacterPlayer::MoveForward(float AxisValue) 
{
    FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

// Move left/right
void ABR_CharacterPlayer::MoveRight(float AxisValue) 
{
    FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

void ABR_CharacterPlayer::Sprint() 
{
	if (bIsCrouched) return;
	ABR_CharacterBase::SetSpeed(SprintSpeed);
	IsSprinting = true;
	CurrentRotationRate = SprintRotationRate;
	TurnDampening = .2f;
}

void ABR_CharacterPlayer::SprintReset() 
{
	ABR_CharacterBase::SetSpeed(MaxSpeed);
	IsSprinting = false;
	CurrentRotationRate = BaseRotationRate;
	TurnDampening = 1.f;
}

void ABR_CharacterPlayer::ToggleCrouch() 
{
	if(bIsCrouched) UnCrouch();
	else Crouch();
}

void ABR_CharacterPlayer::Turn(float AxisValue) 
{
	AddControllerYawInput(AxisValue * TurnDampening);
}

void ABR_CharacterPlayer::BulletTime() 
{
	PlayerStats->BulletTime();
}

// Timeline for aiming zoom
void ABR_CharacterPlayer::SetupTimeline() 
{
	// Bind timeline delegate and add float track
	TimelineProgress.BindUFunction(this, FName("TimelineFloatReturn"));
	FOVTimeline.AddInterpFloat(fCurve, TimelineProgress);

	// Setting FOV
	FOV = Camera->FieldOfView;
	AimFOV = FOV - FOVOffset;

	// Setting timeline's settings before start
	FOVTimeline.SetLooping(false);
}

// FOV Timeline
void ABR_CharacterPlayer::TimelineFloatReturn(float Value) 
{
	Camera->SetFieldOfView(FMath::Lerp(FOV, AimFOV, Value));
}