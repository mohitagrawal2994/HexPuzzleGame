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

};
