#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, +1 max upward speed
	void elevate(float relativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly)
	float maxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float minElevationDegrees = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float maxElevationDegrees = 40.0f;
	
};
