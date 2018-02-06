#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "AimingComponent.h"

#include "Tank.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void aimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void setBarrelReference(UStaticMeshComponent* barrel); 

public:
	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 100000; // Find sensible default
	
};
