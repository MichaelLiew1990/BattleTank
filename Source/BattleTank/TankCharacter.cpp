// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankCharacter.h"


// Sets default values
ATankCharacter::ATankCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATankCharacter::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);
	InputComp->BindAxis("Rotate_Turret", this, &ATankCharacter::RotateTurret);
	InputComp->BindAxis("Elevate_Barrel", this, &ATankCharacter::ElevateBarrel);
	InputComp->BindAxis("Move_Tank", this, &ATankCharacter::MoveTank);
	InputComp->BindAxis("Rotate_Tank", this, &ATankCharacter::RotateTank);
}

void ATankCharacter::MoveTank(float Val)
{
	if (Controller && Val != 0.f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void ATankCharacter::RotateTank(float Val)
{
 	if (!Tank || fabs(Val) < 0.0001) return;
 	float Rot = GetWorld()->DeltaTimeSeconds * Val * RotateSpeed;
// 	Tank->AddRelativeRotation(FRotator(0, Rot, 0));
	AddControllerYawInput(Val);
}

void ATankCharacter::RotateTurret(float Speed)
{
	if (!Turret || fabs(Speed) < 0.0001) return;
	float Rot = GetWorld()->DeltaTimeSeconds * Speed * RotateSpeed;
	Turret->AddRelativeRotation(FRotator(0, Rot, 0));
}

void ATankCharacter::ElevateBarrel(float Speed)
{
	if (!Barrel || fabs(Speed) < 0.0001) return;
	if (Barrel->RelativeRotation.Pitch >= 60 && Speed > 0) return;
	if (Barrel->RelativeRotation.Pitch <= 5 && Speed < 0) return;

	float Rot = GetWorld()->DeltaTimeSeconds * Speed * RotateSpeed;
	Barrel->AddRelativeRotation(FRotator(Rot, 0, 0));
}

void ATankCharacter::SetTurretChildActor(UChildActorComponent* TurretFromBP)
{
	Turret = TurretFromBP;
}

void ATankCharacter::SetBarrelChildActor(UChildActorComponent* BarrelFromBP)
{
	Barrel = BarrelFromBP;
}

void ATankCharacter::SetTankChildActor(UChildActorComponent* TankFromBP)
{
	Tank = TankFromBP;
}

