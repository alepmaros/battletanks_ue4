// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	mProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::launchProjectile(float launchSpeed)
{
	mProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * launchSpeed);
	mProjectileMovementComponent->Activate();
}