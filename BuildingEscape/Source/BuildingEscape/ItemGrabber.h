// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "ItemGrabber.generated.h"

///my struct for two vectors. Just for learning. Should have used Unreal`s native FTwoVectors instead
struct TwoVectors
{
	FVector Start;
	FVector End;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UItemGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float TraceReach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	
	void Grab();
	void Release();

	//Find attached Physics Handle
	void FindPhysicsHandleComponent();

	// Setup attached Input Component
	void SetupInputComponent();

	//Get lineTrace start + end points (for ray-casting)
	TwoVectors GetLineTrace() const;

	//Ray-cast into the distance and return first Physical Body that was hit
	FHitResult GetFirstPhysicsBodyInReach() const;
};
