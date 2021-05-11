// Fill out your copyright notice in the Description page of Project Settings.

#include "ChickenAI_Character.h"
#include "Pickup.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

AChickenAI_Character::AChickenAI_Character() {

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	BoxComp->SetupAttachment(RootComponent);

	//Set spawn delay range
	SpawnDelayRangeLow = 0.5f;
	SpawnDelayRangeHigh = 1.5f;

}

void AChickenAI_Character::Tick(float DeltaTime) {
	PrimaryActorTick.bCanEverTick = true;

	Super::Tick(DeltaTime);

}

void AChickenAI_Character::BeginPlay() {

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AChickenAI_Character::SpawnObject, SpawnDelay, false);

}

void AChickenAI_Character::SpawnObject() {

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpawnEgg Called!"));

	// Get Random Location to spawn at
	FVector SpawnLocation = GetRandomPointInVolume();

	// Get random roation for spawned item
	FRotator SpawnRotation;
	SpawnRotation.Yaw = FMath::FRand() * 360.0f;
	SpawnRotation.Roll = 0.0f;
	SpawnRotation.Pitch = 0.0f;

	// Set the spawn parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	GetWorld()->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AChickenAI_Character::SpawnObject, SpawnDelay, false);

}

FVector AChickenAI_Character::GetRandomPointInVolume() {
	FVector SpawnOrigin = BoxComp->Bounds.Origin;
	FVector SpawnExtent = BoxComp->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}