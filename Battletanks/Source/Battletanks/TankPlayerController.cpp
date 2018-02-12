#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "AimingComponent.h"

/*
This probably need some fixing when there is destruction of the tank and de-posession since the
tank doesnt get updated every single frame
*/

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/// Get the tank that is being possessed
	mControlledTank = getControlledTank();
	if (!ensure(mControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank not found (Is the parent pawn class ATank?)"));
	}

	mAimingComponent = getControlledTank()->FindComponentByClass<UAimingComponent>();
	if (ensure(mAimingComponent))
	{
		FoundAimingComponent(mAimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No aiming component found for TankPlayerController"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	aimTowardsCrosshair();
}

void ATankPlayerController::aimTowardsCrosshair()
{
	if ( !ensure(mAimingComponent) ) { return; }

	FVector hitLocation; 
	if (getSightRayHitLocaiton(hitLocation))
	{
		mAimingComponent->aimAt(hitLocation);
	}
}

// Get World Location of linetrace through crosshair, returning true if it hits landscape
bool ATankPlayerController::getSightRayHitLocaiton(FVector &out_hitLocation) const
{
	// Find the crosshair position
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	FVector2D crossHairPosition = FVector2D(viewPortSizeX * crossHairXLocation, viewPortSizeY * crossHairYLocation);

	FVector lookDirection;
	if (getLookDirection(crossHairPosition, lookDirection))
	{
		return getLookVectorHitLocation(lookDirection, out_hitLocation);
	}

	return false;
}

// Get a unit vector for the look direction of screen position
bool ATankPlayerController::getLookDirection(FVector2D screenPosition, FVector &out_lookDirection) const
{
	// De-projecting screen to world
	FVector worldLocation;
	return DeprojectScreenPositionToWorld(screenPosition.X, screenPosition.Y, worldLocation, out_lookDirection);
}

bool ATankPlayerController::getLookVectorHitLocation(FVector lookDirection, FVector &out_hitLocation) const
{
	FHitResult hitResult;

	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (lookDirection * lineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
			hitResult,
			startLocation,
			endLocation,
			ECollisionChannel::ECC_Visibility
		)
	)
	{
		out_hitLocation = hitResult.Location;
		return true;
	}

	out_hitLocation = FVector(0.0f);
	return false;
}

ATank* ATankPlayerController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

