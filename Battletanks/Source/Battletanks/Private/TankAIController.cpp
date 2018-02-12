#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "AimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/// Get the tank that is being possessed
	mControlledTank = getControlledTank();
	if (!ensure(mControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank on TankAIController not found"));
	}

	/// Get the tank of the player
	mPlayerTank = getPlayerTank();
	if (!ensure(mPlayerTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find the player's tank"), *(GetOwner()->GetName()) );
	}

	mAimingComponent = getControlledTank()->FindComponentByClass<UAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ( !ensure(mPlayerTank && mControlledTank && mAimingComponent) ) { return; }

	MoveToActor(mPlayerTank, acceptanceRadius);

	mAimingComponent->aimAt(mPlayerTank->GetActorLocation());

	mAimingComponent->fire();

}

ATank* ATankAIController::getControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerTank() const
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (ensure(playerController))
	{
		return Cast<ATank>(playerController->GetPawn());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s could not find player controller"), *(GetOwner()->GetName()) );
	}

	return nullptr;
}


