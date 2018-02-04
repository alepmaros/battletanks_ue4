#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/// Get the tank that is being possessed
	mControlledTank = getControlledTank();
	if (mControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank not found (Is the parent pawn class ATank?)"));
	}
}

ATank* ATankPlayerController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

