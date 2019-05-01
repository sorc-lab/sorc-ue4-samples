// Fill out your copyright notice in the Description page of Project Settings.

#include "Missile.h"
#include "Tanks.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

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
