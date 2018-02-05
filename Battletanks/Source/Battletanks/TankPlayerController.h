#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// Start the tank moving the barrel
	void aimTowardsCrosshair();

	// Get World Location of linetrace through crosshair, returning true if it hits landscape
	bool getSightRayHitLocaiton(FVector &out_hitLocation) const;

	//
	bool getLookVectorHitLocation(FVector lookDirection, FVector &hitLocation) const;

	// Get a unit vector for the look direction of screen position
	bool getLookDirection(FVector2D screenPosition, FVector &lookDirection) const;

	ATank* getControlledTank() const;
	
private:
	ATank* mControlledTank = nullptr;

	// Value in % of where the crosshair is
	// (normaly it is on the center of the screen horizontally and 33% vertically)
	UPROPERTY(EditAnywhere)
	float crossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float crossHairYLocation = 0.33333;

	// Default: 10km
	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000.0f;
};
