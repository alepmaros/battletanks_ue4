// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Classes/Components/StaticMeshComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpuse, const FHitResult &Hit)
{

}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
	UStaticMeshComponent *tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2.0f; // two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::setThrottle(float throttle)
{
	FVector forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent *tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}