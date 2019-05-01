// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"
#include "Tanks.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "WorldCollision.h"
#include "Engine/World.h"
#include "DamageInterface.h"

AMissile::AMissile()
{
	PrimaryActorTick.bCanEverTick = true;

	Speed = 200.0f;
	Radius = 20.0f;
	DirectDamage = 5;
}

void AMissile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &AMissile::Explode, 1.0f);
}

void AMissile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector ActorLoc = GetActorLocation();
	FVector Target = ActorLoc + ((DeltaTime * Speed) * GetTransform().GetUnitAxis(EAxis::X));

	FlyMissile(ActorLoc, Target);
}

void AMissile::FlyMissile(FVector ActorLoc, FVector Target)
{
	if (UWorld* World = GetWorld())
	{
		FHitResult OutHit;

		FCollisionShape CollisionShape;
		CollisionShape.SetCapsule(Radius, 200.0f);

		// Sweep a shape against the world and return the first blocking hit using a specific
		// profile. Returns true if OutHit contains any blocking hit entries.
		bool hit = World->SweepSingleByProfile(
			OutHit,
			ActorLoc,
			Target,
			FQuat::Identity,
			MovementCollisionProfile, // FName exposed to Blueprints
			CollisionShape);

		if (hit)
		{
			SetActorLocation(OutHit.Location);

			if (IDamageInterface * DamageActor = Cast<IDamageInterface>(OutHit.Actor.Get()))
				DamageActor->ReceiveDamage(DirectDamage);

			Explode();
		}
		else
			SetActorLocation(Target);
	}
}

void AMissile::Explode()
{
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	SetActorEnableCollision(false);
	OnExplode();
}

void AMissile::OnExplode_Implementation() {
	Destroy();
}
