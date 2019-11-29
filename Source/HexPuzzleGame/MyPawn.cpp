// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "HexGridMesh.h"

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
	
	PController = Cast<APlayerController>(GetController());
	PController->bShowMouseCursor = true;
	PController->bEnableClickEvents = true;
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

	//Binding Firing events
	PlayerInputComponent->BindAction("MHold", IE_Pressed, this, &AMyPawn::HoldHex);
	PlayerInputComponent->BindAction("MHold", IE_Released, this, &AMyPawn::ReleaseHex);
}

void AMyPawn::HoldHex()
{
	FHitResult HitResult;
	PController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, HitResult);
	if (HitResult.bBlockingHit)
	{
		if (HitResult.GetActor()->GetClass()->IsChildOf(AHexGridMesh::StaticClass()))
		{
			SelectedHexMesh = Cast<AHexGridMesh>(HitResult.GetActor());
			UE_LOG(LogTemp, Warning, TEXT("Got The hexmesh"));
		}
	}
}

void AMyPawn::ReleaseHex()
{
	SelectedHexMesh = NULL;
	UE_LOG(LogTemp, Warning, TEXT("Released The mouse"));
}

