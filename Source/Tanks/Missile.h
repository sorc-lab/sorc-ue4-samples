// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Do I always need this?
#include "GameFramework/Actor.h"
#include "Missile.generated.h"

UCLASS()
class TANKS_API AMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMissile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** How fast the missile flies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed;

	/** This missile's radius for collisions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Radius;

	/** How hard this missile hits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int32 DirectDamage;

	/** Describes what this missile hits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName MovementCollisionProfile;

protected:
	void Explode();
	FTimerHandle ExplodeTimerHandle;

	/** What to do when the projectile explodes. The base version just destroys the projectile. */
	UFUNCTION(BlueprintNativeEvent, Category = "Projectile")
	void OnExplode();

	virtual void OnExplode_Implementation();
};
