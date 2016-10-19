// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);
	InputComp->BindAxis("Rotate_Turret", this, &ATank::RotateTurret);
	InputComp->BindAxis("Elevate_Barrel", this, &ATank::ElevateBarrel);
	InputComp->BindAxis("Move_Tank", this, &ATank::MoveTank);
	InputComp->BindAxis("Rotate_Tank", this, &ATank::RotateTank);
}

void ATank::MoveTank(float Speed)
{
	if (!Tank || fabs(Speed) < 0.0001) return;
	float move = GetWorld()->DeltaTimeSeconds * Speed * MoveSpeed;
	Tank->AddRelativeLocation(Tank->GetForwardVector() * move);
}

void ATank::RotateTank(float Speed)
{
	if (!Tank || fabs(Speed) < 0.0001) return;
	float Rot = GetWorld()->DeltaTimeSeconds * Speed * RotateSpeed;
	Tank->AddRelativeRotation(FRotator(0, Rot, 0));
}

void ATank::RotateTurret(float Speed)
{
	if (!Turret || fabs(Speed) < 0.0001) return;
	float Rot = GetWorld()->DeltaTimeSeconds * Speed * RotateSpeed;
	Turret->AddRelativeRotation(FRotator(0, Rot, 0));
}

void ATank::ElevateBarrel(float Speed)
{
	if (!Barrel || fabs(Speed) < 0.0001) return;
	if (Barrel->RelativeRotation.Pitch >= 60 && Speed > 0) return;
	if (Barrel->RelativeRotation.Pitch <= 5 && Speed < 0) return;

	float Rot = GetWorld()->DeltaTimeSeconds * Speed * RotateSpeed;
	Barrel->AddRelativeRotation(FRotator(Rot, 0, 0));
}

void ATank::SetTurretChildActor(UChildActorComponent* TurretFromBP)
{
	Turret = TurretFromBP;
}

void ATank::SetBarrelChildActor(UChildActorComponent* BarrelFromBP)
{
	Barrel = BarrelFromBP;
}

void ATank::SetTankChildActor(UChildActorComponent* TankFromBP)
{
	Tank = TankFromBP;
}

