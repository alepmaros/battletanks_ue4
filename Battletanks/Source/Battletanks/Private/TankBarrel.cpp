#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);
	float elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = FMath::Clamp<float>(RelativeRotation.Pitch + elevationChange, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(newElevation, 0, 0));
}