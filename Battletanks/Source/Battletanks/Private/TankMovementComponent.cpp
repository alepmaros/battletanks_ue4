// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::initialiseTracks(UTankTrack *leftTrack, UTankTrack *rightTrack)
{
	mLeftTrack = leftTrack;
	mRightTrack = rightTrack;
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
