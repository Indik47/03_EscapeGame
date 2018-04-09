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

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetLineTrace().End);
	}
}

void UItemGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit)
	{
		// attach physics handle
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			FRotator(0.0f, 0.0f, 0.0f)
		);
	}
	//If we hit some object, attach a physics handle component
	//TODO attach a physics handle
}

void UItemGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))
		PhysicsHandle->ReleaseComponent();
}


//check if PhysicsHandle is attached
void UItemGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
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

TwoVectors UItemGrabber::GetLineTrace() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//get Player ViewPoint position and rotation as OUT parameters
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	
	TwoVectors TraceLine;
	TraceLine.Start = PlayerViewPointLocation;
	//calculate Line Trace End by adding player position with the vector pointing to where the player is looking
	TraceLine.End = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * TraceReach;;

	return TraceLine;
}

FHitResult UItemGrabber::GetFirstPhysicsBodyInReach() const
{
	TwoVectors TraceLinePoints = GetLineTrace();
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		TraceLinePoints.Start,
		TraceLinePoints.End,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()))
	}

	return Hit;
}





