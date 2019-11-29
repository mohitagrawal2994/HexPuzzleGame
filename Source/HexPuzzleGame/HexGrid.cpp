// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGrid.h"
#include "HexGridMesh.h"
#include "Engine/World.h"

// Sets default values
AHexGrid::AHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	xGridsize = 5;
	yGridsize = 5;

	xOffset = 15.25;
	yOffset = 8.65;
	yDisplace = 17.446;

	CalcYPos = 0;
}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();

	SpawnGrid();
	
}

// Called every frame
void AHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexGrid::SpawnGrid()
{
	int i = 0;
	int j = 0;

	for (i = 0; i < xGridsize; i++)
	{
		for (j = 0; j < yGridsize; j++)
		{
			if (HexagonMesh != NULL)
			{
				if (GetWorld())
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = Instigator;

					if (i % 2 == 0)
					{
						CalcYPos = (yDisplace*j);
					}
					else
					{
						CalcYPos = (yDisplace*j) + yOffset;
					}
					SpawnedItemsArray[i][j] = GetWorld()->SpawnActor<AHexGridMesh>(HexagonMesh, FVector(xOffset * i, CalcYPos, 0), FRotator(0, 0, 0), SpawnParams);
				}
			}
		}
	}
}


