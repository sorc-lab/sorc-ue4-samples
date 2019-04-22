// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Go to Project -> your project name's Properties -> NMake -> IncludePath (click Edit) and it will open paths. drag
// to the end, at empty space, put those included path.

// Project->UE4 Properties->NMake

// Make sure you've added the Paper2D module to your build.cs file under private dependency modules. Then right click
// your .uproject file in the file explorer and select generate project files. This will update your include
// directories to include the files under the Paper2D module.

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ArrowComponent.h"
#include "PaperSpriteComponent.h"
#include "Tank.generated.h"

class UArrowComponent;
class UPaperSpriteComponent;

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// NOTE: UPROPERTY(s) are garbage collected by the engine

	// Helpful debug tool - which way is the tank facing?
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* TankDirection;

	// Sprite for the tank body
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* TankSprite;
};
