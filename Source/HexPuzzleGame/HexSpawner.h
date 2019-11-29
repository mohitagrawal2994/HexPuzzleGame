// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexSpawner.generated.h"

UCLASS()
class HEXPUZZLEGAME_API AHexSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Creating an area where the hex tiles will be spawned
	UPROPERTY(EditAnywhere, Category = "BoxComponent")
	class UBoxComponent* HexSpawnBox;

	//The spawned mesh
	class AHexGridMesh* MySpawnedHexMesh;

public:	
	// Sets default values for this actor's properties
	AHexSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Boolean to allow spawning
	bool CanSpawnHex;

	//Mesh to spawn in spawn area
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	TSubclassOf<class AHexGridMesh> HexagonMesh;

	//Function to spawn the mesh at desired box component location
	void SpawnHexagonMesh();

};
