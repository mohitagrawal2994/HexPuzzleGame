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

	//Pointer to store the dynamic material instance
	UMaterialInstanceDynamic* HexDynamicMaterial;

	//Array that stores the 2d textures of alpha of numbers
	UPROPERTY(EditDefaultsOnly, Category = "MaterialDetails")
	TArray<UTexture2D*> AlphaArray;

	//Grid's current tile value
	int TileValue;

	//Boolean to store whether the piece can be moved
	bool CanMoveMesh;

	//Boolean to say whether the piece can hold any value(For GridMesh)
	bool CanHoldValue;

public:
	// Sets default values for this actor's properties
	AHexGridMesh();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* HexTileMesh;

	//String to hold the materials parameter's name
	UPROPERTY(EditDefaultsOnly, Category = "MaterialDetails")
	FName ColorParamName;

	UPROPERTY(EditDefaultsOnly, Category = "MaterialDetails")
	FName NumberParamName;

	//Function to return the tile value of the hexagon
	int GetValue();

	//Function to set the random number value assigned to it
	void SetValue(int Gvalue);

	//Function to set the material on the hexagon based on tilevalue
	void SettingMaterials();

	//Function to unlock the mesh movement
	void UnlockMesh();
	
	//Function to lock the mesh into its current position
	bool LockMeshOntoGrid();

	//Function to return the status of the current/selected mesh
	bool GetMeshStatus();

	//Functions to get set and return the status of can hold value
	void SetCanHoldValue(bool CH);
	bool GetCanHoldValue();

	//UFUNCTION()
	//void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
