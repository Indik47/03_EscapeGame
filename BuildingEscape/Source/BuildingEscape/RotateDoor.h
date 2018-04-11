// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "RotateDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API URotateDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotateDoor();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool TimeToCloseDoor(float lastDoorOpenTime);

private:
	UPROPERTY(EditAnywhere)
	float openDoorAngle = 90.0f;
	
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 0.5f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;
	AActor* Owner = nullptr;

	float lastDoorOpenTime;
	float GetOverallWeightOnPressurePlate();
	
};
