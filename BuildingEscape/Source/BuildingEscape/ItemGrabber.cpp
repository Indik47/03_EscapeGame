// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemGrabber.h"
#include "EngineMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#define OUT
// Sets default values for this component's properties
UItemGrabber::UItemGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UItemGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if physics handle is attached
	//move object every frame
}

void UItemGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

		//try and reach actor with physics body collision channel set
		GetFirstPhysicsBodyInReach();

	//If we hit some object, attach a physics handle component
	//TODO attach a physics handle
}

void UItemGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))
		//TODO release physics handle
}


//check if PhysicsHandle is attached
void UItemGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handle attached"), *GetOwner()->GetName())
	}
}

void UItemGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has input component found"), *GetOwner()->GetName())
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UItemGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UItemGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no input component attached"), *GetOwner()->GetName())
	}
}

FHitResult UItemGrabber::GetFirstPhysicsBodyInReach() const
{
	FVector PlayerLocation;// = GetWorld()->GetFirstPlayerController()->GetActorLocation;
	FRotator PlayerRotation;// = GetWorld()->GetFirstPlayerController()->GetActorRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);
	FVector TraceLineEnd = PlayerLocation + PlayerRotation.Vector()*Reach;

	
	FHitResult Hit;
	FCollisionQueryParams Param(FName(TEXT("")), false, GetOwner());

	///raytrace into the world and see what we hit
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		TraceLineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		Param
	);

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s was hit!"), *HitActor->GetName());
	}
	return FHitResult();
}

