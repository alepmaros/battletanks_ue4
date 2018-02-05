// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

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
		UE_LOG(LogTemp, Warning, TEXT("%s could not find the player's tank"), *(GetOwner()->GetName()))
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
		APawn* playerPawn = playerController->GetPawn();
		if (playerPawn != nullptr)
		{
			return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not find pawn from player controller"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find player controller"));
	}

	return nullptr;
}


