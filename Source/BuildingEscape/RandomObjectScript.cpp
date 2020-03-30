// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomObjectScript.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
URandomObjectScript::URandomObjectScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URandomObjectScript::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("The Object Name is: %s"), *GetOwner()->GetName());
	
	//both of these do the exact same thing
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();
	FString ObjectTransform = GetOwner()->GetTransform().GetLocation().ToString();
	
	UE_LOG(LogTemp, Warning, TEXT("%s's location is: %s"), *GetOwner()->GetName(), *ObjectPosition);
	// ...
}

// Called every frame
void URandomObjectScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
