// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAimingComponent::aimAt(FVector hitLocation, float launchSpeed)
{
	if (mBarrel == nullptr) { return; }
	
	FVector launchVelocity;
	FVector startLocation = mBarrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			launchVelocity,
			startLocation,
			hitLocation,
			launchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{
		FVector aimDirection = launchVelocity.GetSafeNormal();
		moveBarrel(aimDirection);
	}
	
}

void UAimingComponent::moveBarrel(FVector aimDirection)
{
	FRotator barrelRotation = mBarrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - barrelRotation;
	// work out diference difference between 
}

void UAimingComponent::setBarrelReference(UStaticMeshComponent* barrel)
{
	mBarrel = barrel;
}
