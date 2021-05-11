// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	RootComponent = BoxComp;

	//Set spawn delay range
	SpawnDelayRangeLow = 0.5f;
	SpawnDelayRangeHigh = 1.5f;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnObject, SpawnDelay, false);

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnVolume::SpawnObject() {

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

	GetWorld()->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation,SpawnParams);

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnObject, SpawnDelay, false);

}

FVector ASpawnVolume::GetRandomPointInVolume() {
	FVector SpawnOrigin = BoxComp->Bounds.Origin;
	FVector SpawnExtent = BoxComp->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

