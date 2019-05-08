// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "Tank.generated.h"

USTRUCT(BlueprintType)
struct FTankInput
{
	GENERATED_BODY()

public:
	// Sanitized movement input, usable for game logic.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
	FVector2D MovementInput;

	// These are 1 bit bools. If you use bool then it will use 4 bits. If you use a lot of these it could inflate your
	// structure. This is a smaller way to store boolean values in a struct.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
	uint32 bFire1 : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
	uint32 bFire2 : 1;

	void Sanitize();

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

	void Fire1(bool bPressed);
	void Fire2(bool bPressed);

private:
	//~ Code only. Blueprints should not need to know about this. This should not be used for game logic.
	FVector2D RawMovementInput;
};

UCLASS(abstract)
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	/** The name of the socket at the muzzle - used for spawning missiles. */
	static const FName MuzzleSocketName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	FORCEINLINE const FTankInput& GetCurrentInput() const { return TankInput; }

private:
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

	void Fire1Pressed();
	void Fire1Released();

	void Fire2Pressed();
	void Fire2Released();

private:
	// NOTE: UPROPERTY(s) are garbage collected by the engine

	// Helpful debug tool - which way is the tank facing?
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* TankDirection;

	// Sprite for the tank body
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* TankSprite;

	// The actor used as the turret: This spawns the actor and manages it automatically on spawn/de-spawn etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildTurret;

	// In-game camera
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	// Current input for our tank. Sanitized in Tick().
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input", meta = (AllowPrivateAccess = "true"))
	FTankInput TankInput;

protected:
	// Top speed for our tank. Tank's velocity will be clamped to this magnitude.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float MoveSpeed;

	// Acceleration for our tank, when player is trying to move or change directions.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float MoveAccel;

	// Turn speed (in degrees) for our tank. Tank will only turn while moving.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float YawSpeed;
};
