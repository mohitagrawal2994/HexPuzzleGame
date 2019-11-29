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

	class AHexGridMesh* SpawnedItemsArray[5][5];

	void SpawnGrid();
};
