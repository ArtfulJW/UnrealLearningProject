// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChickenAI_Character.generated.h"


UCLASS()
class LEARNINGPROJECT_API AChickenAI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChickenAI_Character();

	UPROPERTY()
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void SpawnObject();

	UFUNCTION()
	FVector GetRandomPointInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;

private:

	float SpawnDelay;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
