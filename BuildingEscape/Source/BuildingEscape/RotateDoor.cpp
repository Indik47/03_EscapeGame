// Fill out your copyright notice in the Description page of Project Settings.

#include "RotateDoor.h"
#include "Engine/Engine.h"


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
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
	
	// ...
	
}


// Called every frame
void URotateDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

