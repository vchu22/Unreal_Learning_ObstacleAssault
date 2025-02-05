// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime) 
{
	// Move platform forward
		// Get current location
	FVector CurrentLocation = GetActorLocation();
		// Add vector to that location
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		// Set the location
	SetActorLocation(CurrentLocation);
	// Send platform back if gone too far
		// Check how far we've moved
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
		// Reverse direction of motion if gone too far
	if (DistanceMoved >= MoveDistance) 
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;

		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Overshoot: %f"), *Name, Overshoot);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime) 
{
	UE_LOG(LogTemp, Display, TEXT("%s Rotating..."), *GetName());
}