#include "Tank.h"
#include "TankBarrel.h"
#include "TankTrack.h"
#include "Projectile.h"
#include "AimingComponent.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as it is added at constructor
	mTankAimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::setTracksReferences(UTankTrack * leftTrack, UTankTrack * rightTrack)
{
	mLeftTrack = leftTrack;
	mRightTrack = rightTrack;
}

void ATank::aimAt(FVector hitLocation)
{
	mTankAimingComponent->aimAt(hitLocation, launchSpeed);
}

void ATank::fire()
{
	bool hasReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if (!hasReloaded || mBarrel == nullptr || !projectileBlueprint) { return; }

	float time = GetWorld()->DeltaTimeSeconds;

	AProjectile *projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileBlueprint,
		mBarrel->GetSocketLocation(FName("Projectile")),
		mBarrel->GetSocketRotation(FName("Projectile"))
		);

	projectile->launchProjectile(launchSpeed);

	lastFireTime = FPlatformTime::Seconds();
}

void ATank::setBarrelReference(UTankBarrel *barrel)
{
	mBarrel = barrel;
	mTankAimingComponent->setBarrelReference(barrel);
}

void ATank::setTurretReference(UTankTurret *turret)
{
	mTankAimingComponent->setTurretReference(turret);
}

