// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretDirection"));

	// https://github.com/teunw/UE4-Tanks/blob/master/Source/Tanks/Turret.cpp
	TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection"));
	TurretDirection->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TurretSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TurretSprite"));
	TurretSprite->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//RootComponent = Cast<USceneComponent>(CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection")));
	//RootComponent = TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection"));

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

