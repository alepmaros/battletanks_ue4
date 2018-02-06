// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAimingComponent();

public:	
	void aimAt(FVector hitLocation, float launchSpeed);

	void setBarrelReference(UStaticMeshComponent *barrel);

private:
	void moveBarrel(FVector aimDirection);

private:
	UStaticMeshComponent* mBarrel = nullptr;
	
};
