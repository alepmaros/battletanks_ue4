// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void intendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void intendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void initialiseTracks(UTankTrack *leftTrack, UTankTrack *rightTrack);

private:
	UTankTrack *mLeftTrack = nullptr;
	UTankTrack *mRightTrack = nullptr;

};
