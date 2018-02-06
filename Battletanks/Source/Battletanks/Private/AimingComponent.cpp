#include "AimingComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UAimingComponent::aimAt(FVector hitLocation, float launchSpeed)
{
	if (mBarrel == nullptr || mTurret == nullptr) { return; }
	
	FVector launchVelocity;
	FVector startLocation = mBarrel->GetSocketLocation(FName("Projectile"));

	bool foundAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (foundAimingSolution)
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
	
	mBarrel->elevate(deltaRotator.Pitch);
	mTurret->rotate(deltaRotator.Yaw);

}

void UAimingComponent::setBarrelReference(UTankBarrel* barrel)
{
	mBarrel = barrel;
}

void UAimingComponent::setTurretReference(UTankTurret * turret)
{
	mTurret = turret;
}
