// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridMesh.generated.h"

UCLASS()
class HEXPUZZLEGAME_API AHexGridMesh : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

	//Grid's current tile value
	int TileValue;

public:
	// Sets default values for this actor's properties
	AHexGridMesh();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* HexTileMesh;

};
