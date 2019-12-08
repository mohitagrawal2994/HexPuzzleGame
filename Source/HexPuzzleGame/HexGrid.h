// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"

UCLASS()
class HEXPUZZLEGAME_API AHexGrid : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float CalcYPos;

	//Variable to store the minimum distance the hexmesh has to move
	float MinX;
	float MinY;

	//Variable to store grid space
	float XSpace;
	float YSpace;
	float XErrorTolerance;

	//Variable to Store the last mesh mesh placed
	class AHexGridMesh* OnGridMesh;

	//Array to store the spawned actors
	class AHexGridMesh* SpawnedItemsArray[5][5];

	//Variable to store the spawned actors index of adjoining spawns
	TArray<int32> ArrayRow;
	TArray<int32> ArrayColumn;

	//Variable to store the last placed spawned mesh index
	int MeshRow;
	int MeshColumn;

public:	
	// Sets default values for this actor's properties
	AHexGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	float xOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	float yOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	float yDisplace;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int xGridsize;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	int yGridsize;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	TSubclassOf<class AHexGridMesh> HexagonMesh;

	//Function to spawn the actors
	void SpawnGrid();

	//Function to add the meshes onto the grid
	bool AddToGrid(FVector BBoxLocation, class AHexGridMesh* ITMesh);

	//Function to find the neighbouring Hexagons
	void FindAdjoiningHex();

	//Function to consolidate the hexes according to the neighbours
	void HexConsolidate();

	//Function to add to array index
	void AddToIndex(int x, int y);
};
