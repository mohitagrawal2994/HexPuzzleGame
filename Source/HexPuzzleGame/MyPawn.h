// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class HEXPUZZLEGAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

private :
	UPROPERTY(EditDefaultsOnly,  Category = "Camera")
	class UCameraComponent* OrthoCameraComponent;

	//Empty class to hold the player controller
	class APlayerController* PController;

	//Empty class to hold the actors which got hit on click
	class AHexGridMesh* SelectedHexMesh;

	//Vectors to hold the current cursor position
	FVector WorldLocation;
	FVector WorldDirection;

	//Boolean to check if holding any object
	bool CanHoldHex;

	//Boolean to say that the new spawner is ready to spawn
	bool IsReadyToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Function that binds the user functionality
	void HoldHex();

	void ReleaseHex();

	//Variable to store Current HexSpawner in scene
	UPROPERTY(EditAnywhere, Category = "Hexagon Spawner")
	class AHexSpawner* CurrentHexSpawner;

};
