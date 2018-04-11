// Fill out your copyright notice in the Description page of Project Settings.

#include "RotateDoor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h" 
#include "EngineMinimal.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
URotateDoor::URotateDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotateDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	//pressure plate not assigned (nullptr protection)
	if (pressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate (opening trigger) not assigned to %s! (nullptr)"), *Owner->GetName())
	}
	// ...

}

void URotateDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, openDoorAngle, 0.0f));
}

void URotateDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void URotateDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!pressurePlate)  {	return;	}		//nullptr protection

	//Poll the trigger volume
	if (GetOverallWeightOnPressurePlate() > 35.f)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (TimeToCloseDoor(lastDoorOpenTime))
	{
		CloseDoor();
	}
	// ...
}

bool URotateDoor::TimeToCloseDoor(float lastDoorOpenTime)

{
	return GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay;
}

float URotateDoor::GetOverallWeightOnPressurePlate()
{
	float OverallWeight = 0.f;
	//find all actors inside trigger Pressure Plate


	TArray<AActor*> OverlappingActors;
	pressurePlate->GetOverlappingActors(OUT OverlappingActors);

	//iterate through them to find overall weight
	for (auto* Actor : OverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName())
		OverallWeight += Actor->FindComponentByClass<UPrimitiveComponent>()->CalculateMass();
	}
	return OverallWeight;
}



