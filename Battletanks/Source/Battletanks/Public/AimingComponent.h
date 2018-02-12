#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

public:	
	void aimAt(FVector hitLocation);

	void setBarrelReference(UTankBarrel *barrel);
	void setTurretReference(UTankTurret *turret);

	UFUNCTION(BlueprintCallable, Category = Input)
	void setTankReferences(UTankBarrel *barrel, UTankTurret *turret);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void fire();

private:
	void moveBarrel(FVector aimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState mFiringState = EFiringState::Locked;

private:
	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float mLaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double reloadTimeInSeconds = 2.0f;

	double lastFireTime = 0.0f;
	
};
