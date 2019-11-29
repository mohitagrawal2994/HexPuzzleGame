// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHexGridMesh::AHexGridMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileValue = 0;
	HexTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexTileMesh"));
	RootComponent = HexTileMesh;

}

// Called when the game starts or when spawned
void AHexGridMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexGridMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

