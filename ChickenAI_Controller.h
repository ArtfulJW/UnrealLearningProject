// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChickenAI_Controller.generated.h"


UCLASS()
class LEARNINGPROJECT_API AChickenAI_Controller : public AAIController
{
	GENERATED_BODY()
	
public:

	AChickenAI_Controller();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Wander();

	UFUNCTION()
	bool GetRandomPointInRadius(FVector& Origin, FVector& OutResult);

	FVector Destination;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


};
