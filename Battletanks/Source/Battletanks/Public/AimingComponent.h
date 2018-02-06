#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

public:	
	void aimAt(FVector hitLocation, float launchSpeed);

	void setBarrelReference(UTankBarrel *barrel);
	void setTurretReference(UTankTurret *turret);

private:
	void moveBarrel(FVector aimDirection);

private:
	UTankBarrel* mBarrel = nullptr;
	UTankTurret* mTurret = nullptr;
	
};
