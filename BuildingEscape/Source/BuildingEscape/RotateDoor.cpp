// Fill out your copyright notice in the Description page of Project Settings.

#include "RotateDoor.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h" 
#include "EngineMinimal.h"


// Sets default values for this component's properties
URotateDoor::URotateDoor ()
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

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	
	// ...
	
}

void URotateDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, openDoorAngle, 0.0f);
	Owner->SetActorRotation(NewRotation);
}

void URotateDoor::CloseDoor()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void URotateDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the trigger volume
	//If the ActorThatOpensDoor is in the volume of the trigger
	if (pressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
	OpenDoor();
	}
	else
	{
		CloseDoor();
	}
	// ...
}

