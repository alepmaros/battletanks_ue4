// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::setThrottle(float throttle)
{
	
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s %f %s %s"), *GetName(), throttle, *forceApplied.ToString(), *forceLocation.ToString());
	UPrimitiveComponent *tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}