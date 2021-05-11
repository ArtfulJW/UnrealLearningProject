// Fill out your copyright notice in the Description page of Project Settings.


#include "Conveyor.h"
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Misc/App.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"

// Sets default values
AConveyor::AConveyor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	RootComponent = MeshComp;

	BoxComp->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepWorldTransform);

}

// Called when the game starts or when spawned
void AConveyor::BeginPlay()
{
	Super::BeginPlay();
	
	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, & AConveyor::OnBoxOverlap);

}

// Called every frame
void AConveyor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Call to check overlapping actors every tick.
	
	ConveyorMove(DeltaTime);
}

void AConveyor::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	/*
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, AActor::StaticClass());

	for (int x = 0; x < OverlappingActors.Num(); x++) {
		
		//Add Actor World Offset
		FVector Forward = this->GetActorForwardVector();
		float Speed = 2.0f;
		
		OverlappingActors[x]

	}
	

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {

		ConveyorMove(OtherActor);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Pushing!")));

		OnBoxOverlap(OverlappedComponent,OtherActor,OtherComp,OtherBodyIndex,bFromSweep,SweepResult);

	}
	*/
}

void AConveyor::ConveyorMove(float DeltaTime){
	/*
	FVector Forward = this->GetActorForwardVector();
	float Speed = 20.0f;
	OtherActor->AddActorWorldOffset(Forward*Speed, true);
	*/

	// Initialize Arrayt of Type Actor
	TArray<AActor*> OverlappingActors;

	// Returns array of overlapping Actors
	GetOverlappingActors(OverlappingActors, APickup::StaticClass());

	FVector Forward = this->GetActorForwardVector();
	float Speed = 200.0f;

	for (AActor* Actor : OverlappingActors) {

		Actor->AddActorWorldOffset((Speed*DeltaTime) * Forward);

		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Moving!")));

	}

}

