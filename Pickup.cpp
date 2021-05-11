// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "GameCharacter.h"
#include "Templates/SubclassOf.h"
#include "Engine/LatentActionManager.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectBase.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	// Set Static Mesh as root component so SFX will be based on the root component's location and size.
	RootComponent = BoxComp;
	MeshComp->AttachToComponent(BoxComp, FAttachmentTransformRules::KeepWorldTransform);
	SphereComp->AttachToComponent(BoxComp, FAttachmentTransformRules::KeepWorldTransform);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBoxOverlap);


	Super::BeginPlay();

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector NewLocation = MeshComp->GetComponentLocation();

	// Floating Animation
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	// Scale our height by a factor of 20
	//NewLocation.Z += DeltaHeight * 20.0f;
	// Rotate by 20 Degrees per second
	float DeltaRotation = DeltaTime * 20.0f;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);

}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	/*
	// Initialize Arrayt of Type Actor
	TArray<AActor*> OverlappingActors;

	// Returns array of overlapping Actors
	OverlappedComponent->GetOverlappingActors(OverlappingActors, TSubclassOf<ACharacter>());

	
	for (AActor* Actor : OverlappingActors) {
		MoveTo(OtherActor);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Hit: %s"), *OtherActor->GetName()));

	}
	*/
	
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherActor->IsA(AGameCharacter::StaticClass())) && (OtherComp != NULL)) {

		MoveTo(OtherActor);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));

	}
	

}

void APickup::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	/*
	// Initialize Arrayt of Type Actor
	TArray<AActor*> OverlappingActors;

	// Returns array of overlapping Actors
	OverlappedComponent->GetOverlappingActors(OverlappingActors, TSubclassOf<ACharacter>());

	for (AActor* Actor : OverlappingActors) {

		if (OtherActor) {

		}

		//Destroy();
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Destroy!")));

	}
	*/
	
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherActor->IsA(AGameCharacter::StaticClass())) && (OtherComp != NULL)) {

		Destroy();
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Destroy!"));

	}
	
}

void APickup::MoveTo(AActor* OtherActor) {

	FVector Location = OtherActor->GetActorLocation();
	FRotator Rotation = OtherActor->GetActorRotation();
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	
	UKismetSystemLibrary::MoveComponentTo(BoxComp, Location, Rotation, false, true, 0.2f, true, EMoveComponentAction::Move, LatentInfo);

}


