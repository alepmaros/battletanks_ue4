// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	ATank* getControlledTank() const;
	ATank* getPlayerTank() const;

private:
	ATank* mControlledTank = nullptr;
	ATank* mPlayerTank = nullptr;
	
	
};