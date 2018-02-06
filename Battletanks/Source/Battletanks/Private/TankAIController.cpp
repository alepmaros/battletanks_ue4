#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/// Get the tank that is being possessed
	mControlledTank = getControlledTank();
	if (mControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank on TankAIController not found"));
	}

	/// Get the tank of the player
	mPlayerTank = getPlayerTank();
	if (mPlayerTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find the player's tank"), *(GetOwner()->GetName()) );
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mPlayerTank != nullptr)
	{
		if (mControlledTank != nullptr)
		{
			mControlledTank->aimAt(mPlayerTank->GetActorLocation());
		}
	}
	
}

ATank* ATankAIController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerTank() const
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController != nullptr)
	{
		return Cast<ATank>(playerController->GetPawn());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find player controller"), *(GetOwner()->GetName()) );
	}

	return nullptr;
}


