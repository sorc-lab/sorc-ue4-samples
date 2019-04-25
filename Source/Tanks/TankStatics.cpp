// Fill out your copyright notice in the Description page of Project Settings.


#include "TankStatics.h"

/** Find the smallest angle between two headings (in degrees) */
float UTankStatics::FindDeltaAngleDegrees(float A1, float A2)
{
	// Find the difference
	float Delta = A2 - A1;

	// If change is larger than 180
	if (Delta > 180.0f)
	{
		// Flip to negative equivalent
		Delta = Delta - (360.0f);
	}
	else if (Delta < -180.0f)
	{
		// Otherwise, if change is smaller than -180
		// Flip to positive equivalent
		Delta = Delta + (360.0f);
	}

	// Return delta in [-180,180] range
	return Delta;
}

bool UTankStatics::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle)
{
	FVector2D Normal = (Target - Start); // Always use END - START in vector math

	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}

	return false;
}
