// Fill out your copyright notice in the Description page of Project Settings.

#include "ChickenAI_Controller.h"
#include "ChickenAI_Character.h"
#include "AIController.h"
#include "Actions/PawnActionsComponent.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"



AChickenAI_Controller::AChickenAI_Controller() {

}

// Called every frame
void AChickenAI_Controller::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AChickenAI_Controller::BeginPlay(){

	Super::BeginPlay();

	Destination.X = -247.0f;
	Destination.Y = 60.0f;
	Destination.Z = 78.0f;
	
	AAIController::MoveToLocation(Destination);

}

void AChickenAI_Controller::Wander() {
	/*
	FVector StartPos = GetPawn()->GetActorLocation();
	//GetRandomPointInRadius(StartPos, Destination);

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Calculating!"));

	if (!(StartPos.Equals(Destination,0.01f))) {

		AAIController::MoveToLocation(Destination,10.0f,true,true,false,true);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, StartPos.ToString());
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Destination.ToString());
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Movin!"));

	} else {

		GetRandomPointInRadius(StartPos, Destination);
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Calculating!"));
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, StartPos.ToString());
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Destination.ToString());

		

	}
	*/

	FVector StartPos = GetPawn()->GetActorLocation();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, StartPos.ToString());
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Destination.ToString());

	if (StartPos.Equals(Destination, 0.01f)) {

		GetRandomPointInRadius(StartPos, Destination);
		AAIController::MoveToLocation(Destination);

	}

}

bool AChickenAI_Controller::GetRandomPointInRadius(FVector& Origin, FVector& OutResult) {

	float SearchRadius = 9000.0f;

	if (GetWorld()) {

		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

		if (NavSys) {

			FNavLocation ResultLocation;
			
			bool bSuccuss = NavSys->GetRandomReachablePointInRadius(Origin,SearchRadius,ResultLocation);

			OutResult = ResultLocation;

			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Got New coords!"));

			return bSuccuss;
		}

		return false;
	}

	return false;
}

void AChickenAI_Controller::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {

	Super::OnMoveCompleted(RequestID, Result);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Moves!"));
}