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
	// Called from the pathfinding logic by the AI Controllers
	virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack *mLeftTrack = nullptr;
	UTankTrack *mRightTrack = nullptr;

};
