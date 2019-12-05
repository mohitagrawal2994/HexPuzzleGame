// Fill out your copyright notice in the Description page of Project Settings.


#include "HexSpawner.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "HexGridMesh.h"

// Sets default values
AHexSpawner::AHexSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HexSpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HexSpawnBox"));
	RootComponent = HexSpawnBox;
}

// Called when the game starts or when spawned
void AHexSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//Spawning the first hex
	SpawnHexagonMesh();

}

void AHexSpawner::SpawnHexagonMesh()
{
	if (HexagonMesh != NULL)
	{
		if (GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			MySpawnedHexMesh = GetWorld()->SpawnActor<AHexGridMesh>(HexagonMesh, HexSpawnBox->GetComponentLocation(), FRotator(0, 0, 0), SpawnParams);

			MySpawnedHexMesh->SetValue(FMath::RandRange(1,3));
			MySpawnedHexMesh->SettingMaterials();
			MySpawnedHexMesh->UnlockMesh();
		}
	}
}

