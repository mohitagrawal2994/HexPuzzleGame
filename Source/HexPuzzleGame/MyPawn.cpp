// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "HexGridMesh.h"
#include "HexSpawner.h"
#include "Engine/World.h"
#include "Engine/Public/EngineUtils.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrthoCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("OrthoCamera"));		//Assigning the camera
	OrthoCameraComponent->SetupAttachment(RootComponent);
	OrthoCameraComponent->RelativeLocation = FVector(15.0, 30.0f, 150.0f); // Position the camera
	OrthoCameraComponent->RelativeRotation = FRotator(-90.0, 0.0, 0);
	OrthoCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	OrthoCameraComponent->OrthoWidth = 384;

	PController = NULL;
	SelectedHexMesh = NULL;
	WorldDirection = FVector(0, 0, 0);
	WorldDirection = FVector(0, 0, 0);
	CanHoldHex = false;
	CurrentHexSpawner = NULL;
	IsReadyToSpawn = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	PController = Cast<APlayerController>(GetController());
	PController->bShowMouseCursor = true;
	PController->bEnableClickEvents = true;

	if (GetWorld())
	{
		for (TActorIterator<AActor> MyItr(GetWorld()); MyItr; ++MyItr)
		{
			CurrentHexSpawner = Cast<AHexSpawner>(*MyItr);
			if (CurrentHexSpawner)
			{
				break;
			}
		}
	}

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Updating the hexmesh location according to the mouse position if its movable
	if (CanHoldHex && SelectedHexMesh != NULL)
	{
		PController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		SelectedHexMesh->SetActorLocation(FVector(WorldLocation.X, WorldLocation.Y, 1));
	}

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
	//Checking what was hit by the mouse cursor and then getting that actor's instance details
	FHitResult HitResult;
	PController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (HitResult.bBlockingHit)
	{
		if (HitResult.GetActor()->GetClass()->IsChildOf(AHexGridMesh::StaticClass()))
		{
			SelectedHexMesh = Cast<AHexGridMesh>(HitResult.GetActor());
			if (SelectedHexMesh->GetMeshStatus())
			{
				CanHoldHex = true;
			}
		}
	}
}

void AMyPawn::ReleaseHex()
{
	if (SelectedHexMesh == NULL)
	{
		return;
	}
	//Removing the property to move the mesh
	CanHoldHex = false;

	//Locking the mesh's movement
	IsReadyToSpawn = SelectedHexMesh->LockMeshOntoGrid();
	
	if (IsReadyToSpawn && CurrentHexSpawner)
	{
		CurrentHexSpawner->SpawnHexagonMesh();
	}
	//Removing the mesh instance details
	SelectedHexMesh = NULL;
}

