// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrthoCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("OrthoCamera"));		//Assigning the camera
	OrthoCameraComponent->SetupAttachment(RootComponent);
	OrthoCameraComponent->RelativeLocation = FVector(15.0, 30.0f, 150.0f); // Position the camera
	OrthoCameraComponent->RelativeRotation = FRotator(-90.0, 0.0, 0);

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

