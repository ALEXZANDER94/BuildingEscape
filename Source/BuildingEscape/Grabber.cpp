// Fill out your copyright notice in the Description page of Project Settings.

//required for drawdebugline()
#include "DrawDebugHelpers.h"
//required for getworld()
#include "Engine/World.h"
//required for player viewpoint
#include "GameFramework/PlayerController.h"

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get Players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//The GetPlayerViewPoint takes an FVector and FRotator and assigns them respectively
	//The function itself is void, thus passing in the declared variables will result
	//in them being assigned within the function
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	//If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		//move the object we are holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get Players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//The GetPlayerViewPoint takes an FVector and FRotator and assigns them respectively
	//The function itself is void, thus passing in the declared variables will result
	//in them being assigned within the function
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	// Ray-cast out to a certain distance (Reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	// See what we're hitting

	AActor *ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTrace has hit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

void UGrabber::FindPhysicsHandle()
{
	// Check for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}
void UGrabber::SetupInputComponent()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp)
	{
		//Input Component has been found
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
}
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed"));

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//The GetPlayerViewPoint takes an FVector and FRotator and assigns them respectively
	//The function itself is void, thus passing in the declared variables will result
	//in them being assigned within the function
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	//Try and reach any actors with a physics body collision channel set.
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent *ComponentToGrab = HitResult.GetComponent();

	//If we hit something then attach physics handle.
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd);
	}
}
void UGrabber::Drop()
{
	UE_LOG(LogTemp, Warning, TEXT("Dropped"));
	//TODO remove/release physics handle
	PhysicsHandle->ReleaseComponent();
}