#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UAimingComponent;
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class AProjectile;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UAimingComponent* mTankAimingComponent;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UTankBarrel *barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTurretReference(UTankTurret *turret);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTracksReferences(UTankTrack *leftTrack, UTankTrack *rightTrack);

	void aimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void fire();


private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double reloadTimeInSeconds = 2.0f;

	double lastFireTime = 0.0f;

	UTankBarrel *mBarrel = nullptr;

	UTankTrack *mLeftTrack = nullptr;
	UTankTrack *mRightTrack = nullptr;
};
