// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//required for Physics Handle
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 200.f;

	//required for Physics Handle
	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	//required for Input Component
	UInputComponent *InputComp = nullptr;

	void Grab();
	void Drop();
	void FindPhysicsHandle();
	void SetupInputComponent();

	//Return first Actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
};