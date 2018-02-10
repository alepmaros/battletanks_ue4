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


}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	//mTankAimingComponent = GetComponentBy
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::aimAt(FVector hitLocation)
{
	if ( !ensure(mTankAimingComponent) ) { return; }

	mTankAimingComponent->aimAt(hitLocation, launchSpeed);
}

void ATank::fire()
{
	bool hasReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if ( !ensure(mBarrel && projectileBlueprint) || !hasReloaded) { return; }

	float time = GetWorld()->DeltaTimeSeconds;

	AProjectile *projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileBlueprint,
		mBarrel->GetSocketLocation(FName("Projectile")),
		mBarrel->GetSocketRotation(FName("Projectile"))
		);

	projectile->launchProjectile(launchSpeed);

	lastFireTime = FPlatformTime::Seconds();
}