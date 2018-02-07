// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::setThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *GetName(), throttle);
}