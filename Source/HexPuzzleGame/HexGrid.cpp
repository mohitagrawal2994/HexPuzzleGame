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
	MinX = 0.0;
	MinY = 0.0;
	XSpace = 0.0;
	YSpace = 0.0;
	XErrorTolerance = 12.0;
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
					SpawnedItemsArray[i][j]->LockMesh();
					SpawnedItemsArray[i][j]->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				}
			}
		}
	}
}

bool AHexGrid::AddToGrid(FVector BBoxLocation, AHexGridMesh* ITmesh)
{
	//Get Current Hexagon Mesh Location
	MinX = ITmesh->GetActorLocation().X;
	MinY = ITmesh->GetActorLocation().Y;

	//Finding the maximum space size of the grid
	XSpace = xOffset * (xGridsize - 1);
	YSpace = yDisplace * (yGridsize - 1) + yOffset;
	
	//Check if hexagon mesh outside grid range if then set location to bounding box
	if ((MinX < -XErrorTolerance) || (MinX > (XSpace+XErrorTolerance)) || (MinY < -yOffset) || (MinY > (YSpace+ yOffset)))
	{
		ITmesh->SetActorLocation(BBoxLocation);
		return false;
	}
	else
	{
		//Find the closest hexagon mesh onto the grid where the mesh is to be locked
		//Finding the X Coordinate
		for (int i = 0; i < xGridsize; i++)
		{
			for (int j = 0; j < yGridsize; j++)
			{
				if (FMath::IsNearlyEqual(SpawnedItemsArray[i][j]->GetActorLocation().X, MinX, XErrorTolerance))
				{
					MinX = SpawnedItemsArray[i][j]->GetActorLocation().X;
				}
			}
		}
		//If The Hexagon is in even row then
		if (int(MinX / xOffset) % 2 == 0 )
		{
			//If in Even row skip the odd rows closest location testing
			for (int i = 0; i < xGridsize; i++)
			{
				if (i % 2 == 0)
				{
					for (int j = 0; j < yGridsize; j++)
					{
						if (FMath::IsNearlyEqual(SpawnedItemsArray[i][j]->GetActorLocation().Y, MinY, yOffset))
						{
							MinY = SpawnedItemsArray[i][j]->GetActorLocation().Y;
						}
					}
				}	
			}
		}
		else
		{
			//If in Odd row skip the even rows closest location testing
			for (int i = 0; i < xGridsize; i++)
			{
				if (i % 2 != 0)
				{
					for (int j = 0; j < yGridsize; j++)
					{
						if (FMath::IsNearlyEqual(SpawnedItemsArray[i][j]->GetActorLocation().Y, MinY, yOffset))
						{
							MinY = SpawnedItemsArray[i][j]->GetActorLocation().Y;
						}
					}
				}
			}
		}

		//Find the mesh on grid with the same location
		AHexGridMesh* OnGridMesh = NULL;
		for (int i = 0; i < xGridsize; i++)
		{
			for (int j = 0; j < yGridsize; j++)
			{
				if (SpawnedItemsArray[i][j]->GetActorLocation().X == MinX && SpawnedItemsArray[i][j]->GetActorLocation().Y == MinY)
				{
					OnGridMesh = SpawnedItemsArray[i][j];
					break;
				}
			}
		}

		if (OnGridMesh != NULL)
		{
			//Check whether the grid mesh can hold value
			if (OnGridMesh->GetCanHoldValue())
			{
				//Move the mesh to the new X and Y Location
				ITmesh->SetActorLocation(FVector(MinX, MinY, 1.0f));
				ITmesh->LockMesh();
				OnGridMesh->SetValue(ITmesh->GetValue());
				OnGridMesh->SetCanHoldValue(false);
				OnGridMesh->SettingMaterials();
				ITmesh->Destroy();
				//Return true to spawn a new hexagon
				return true;
			}
			else
			{
				//Resetting the hex cube location to Spawner
				ITmesh->SetActorLocation(BBoxLocation);

				//Returns a false as the point where the hex was placed was not empty
				return false;
			}
		}
		ITmesh->SetActorLocation(BBoxLocation);
		return false;
	}
}


