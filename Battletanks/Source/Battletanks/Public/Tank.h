#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UAimingComponent;
class UTankBarrel;
class UTankTurret;

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

	void aimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UTankBarrel *barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setTurretReference(UTankTurret *turret);

public:
	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 100000; // Find sensible default
	
};
