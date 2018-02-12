// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	ATank* getControlledTank() const;
	ATank* getPlayerTank() const;

private:
	ATank* mControlledTank = nullptr;
	ATank* mPlayerTank = nullptr;
	UAimingComponent *mAimingComponent = nullptr;

	// How close the AI tank will get close to the player
	UPROPERTY(EditDefaultsOnly)
	float acceptanceRadius = 3000;
};
