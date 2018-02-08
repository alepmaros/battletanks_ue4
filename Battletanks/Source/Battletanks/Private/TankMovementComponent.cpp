#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialiseTracks(UTankTrack *leftTrack, UTankTrack *rightTrack)
{
	mLeftTrack = leftTrack;
	mRightTrack = rightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector currentTankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	
	float speedForward = FVector::DotProduct(currentTankForward, aiForwardIntention);
	intendMoveForward(speedForward);

	FVector rotationVector = FVector::CrossProduct(currentTankForward, aiForwardIntention);
	intendTurnRight(rotationVector.Z);

	//UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *GetOwner()->GetName(), speedForward)
}

void UTankMovementComponent::intendMoveForward(float Throw)
{
	if (mLeftTrack == nullptr || mRightTrack == nullptr) { return; }
	mLeftTrack->setThrottle(Throw);
	mRightTrack->setThrottle(Throw);
}

void UTankMovementComponent::intendTurnRight(float Throw)
{
	if (mLeftTrack == nullptr || mRightTrack == nullptr) { return; }
	mLeftTrack->setThrottle(Throw);
	mRightTrack->setThrottle(-Throw);
}
