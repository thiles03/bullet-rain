// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BR_CharacterStats.h"

// Sets default values for this component's properties
UBR_CharacterStats::UBR_CharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBR_CharacterStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBR_CharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

