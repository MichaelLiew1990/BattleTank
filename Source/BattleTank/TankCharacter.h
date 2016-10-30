// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "TankCharacter.generated.h"

UCLASS()
class BATTLETANK_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComp) override;

	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetTurretChildActor(UChildActorComponent* TurretFromBP);

	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetBarrelChildActor(UChildActorComponent* BarrelFromBP);

	UFUNCTION(BlueprintCallable, Category = Tank)
		void SetTankChildActor(UChildActorComponent* TankFromBP);
private:
	void MoveTank(float Speed);
	void RotateTank(float Speed);
	void RotateTurret(float Speed);
	void ElevateBarrel(float Speed);

	//Form Blueprint
	UChildActorComponent* Tank = nullptr;
	//From Blueprint
	UChildActorComponent* Turret = nullptr;
	//From Blueprint
	UChildActorComponent* Barrel = nullptr;
	UPROPERTY(EditAnywhere)
		float RotateSpeed = 120.f;
	UPROPERTY(EditAnywhere)
		float MoveSpeed = 240.f;
};
