// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Tank.h" // I thought this was bad practice?
#include "Turret.generated.h"

UCLASS()
class TANKS_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();
	virtual void Tick(float DeltaTime) override;

	/** The name of the socket at the muzzle - used for spawning missiles. */
	static const FName MuzzleSocketName;

private:
	// Helpful debug tool - which way is the turret facing?
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* TurretDirection;

	// Sprite for the turret body
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* TurretSprite;

	// Tank that owns this turret.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	ATank* Tank;

	// Maximum rate at which the turret can turn to aim.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	float YawSpeed;

	// Time to delay between Fire1 commands.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	float Fire1Cooldown;

	// If this value is greater than the current game time, Fire1 is ignored because it has been fired too recently.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
	float Fire1ReadyTime;

protected:
	virtual void BeginPlay() override;

	// Projectile to spawn when firing.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	TSubclassOf<AActor> Projectile;
};
