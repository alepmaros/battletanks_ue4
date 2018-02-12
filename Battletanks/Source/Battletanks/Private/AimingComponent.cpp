#include "AimingComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Kismet/GameplayStatics.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAimingComponent::BeginPlay()
{
	lastFireTime = FPlatformTime::Seconds();
}

void UAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool hasReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
	if (!hasReloaded)
	{
		mFiringState = EFiringState::Reloading;
	}
	else if (isBarrelMoving())
	{
		mFiringState = EFiringState::Aiming;
	}
	else
	{
		mFiringState = EFiringState::Locked;
	}

}

bool UAimingComponent::isBarrelMoving()
{
	if (!ensure(mBarrel)) { return false; }

	FVector barrelForward = mBarrel->GetForwardVector();

	return !barrelForward.Equals(mAimDirection, 0.01);
}

void UAimingComponent::fire()
{
	
	if (!ensure(mBarrel && projectileBlueprint)) { return; }

	if (mFiringState != EFiringState::Reloading)
	{
		AProjectile *projectile = GetWorld()->SpawnActor<AProjectile>(
			projectileBlueprint,
			mBarrel->GetSocketLocation(FName("Projectile")),
			mBarrel->GetSocketRotation(FName("Projectile"))
			);

		projectile->launchProjectile(mLaunchSpeed);

		lastFireTime = FPlatformTime::Seconds();
	}

}

void UAimingComponent::aimAt(FVector hitLocation)
{
	if ( !ensure(mBarrel && mTurret) ) { return; }
	
	FVector launchVelocity;
	FVector startLocation = mBarrel->GetSocketLocation(FName("Projectile"));

	bool foundAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		mLaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (foundAimingSolution)
	{
		mAimDirection = launchVelocity.GetSafeNormal();
		moveBarrel(mAimDirection);
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

void UAimingComponent::setTankReferences(UTankBarrel *barrel, UTankTurret *turret)
{
	mBarrel = barrel;
	mTurret = turret;
}
