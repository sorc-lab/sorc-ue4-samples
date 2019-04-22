// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Tanks.h"
#include "GameFramework/SpringArmComponent.h" // Didn't see this in tutorial or the 4.18 migrated code
#include "PaperSpriteComponent.h"

void FTankInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FTankInput::MoveX(float AxisValue)
{
	RawMovementInput.X += AxisValue;
}

void FTankInput::MoveY(float AxisValue)
{
	RawMovementInput.Y += AxisValue;
}


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TankBase"));
	}

	TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TankDirection"));
	TankDirection->SetupAttachment(RootComponent);

	// Sprite/phyisical representation of tank is attached to the arrow/direction tool
	TankSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TankSprite"));
	TankSprite->SetupAttachment(TankDirection);

	ChildTurret = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret"));
	ChildTurret->SetupAttachment(TankDirection);

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->CameraLagSpeed = 2.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 1024.0f;
	CameraComponent->AspectRatio = 4.0f / 3.0f;
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraComponent->SetWorldRotation(FRotator(-90.0f, -90.0f, 0.0f));

	/*MoveSpeed = 100.0f;
	MoveAccel = 200.0f;
	YawSpeed = 180.0f;*/
}

void ATank::MoveX(float AxisValue)
{
	TankInput.MoveX(AxisValue);
}

void ATank::MoveY(float AxisValue)
{
	TankInput.MoveY(AxisValue);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankInput.Sanitize();
	UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), TankInput.MovementInput.X, TankInput.MovementInput.Y);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveX", this, &ATank::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATank::MoveY);
}

