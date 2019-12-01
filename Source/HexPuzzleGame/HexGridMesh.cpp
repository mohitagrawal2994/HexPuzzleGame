// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Classes/Materials/MaterialInstanceDynamic.h"

// Sets default values
AHexGridMesh::AHexGridMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TileValue = 0;
	HexTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HexTileMesh"));
	RootComponent = HexTileMesh;
	HexTileMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	ColorParamName = "Color";
	NumberParamName = "Number";

	CanMoveMesh = false;

	HexTileMesh->OnComponentBeginOverlap.AddDynamic(this, &AHexGridMesh::OnOverlapBegin);
	//HexTileMesh->OnComponentEndOverlap.AddDynamic(this, &AHexGridMesh::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AHexGridMesh::BeginPlay()
{
	Super::BeginPlay();
	//Creating a dynamic material with material index 0
	HexDynamicMaterial = HexTileMesh->CreateDynamicMaterialInstance(0);

}

// Called every frame
void AHexGridMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AHexGridMesh::GetValue()
{
	return TileValue;
}

void AHexGridMesh::SetValue(int Gvalue)
{
	TileValue = Gvalue;
}

void AHexGridMesh::SettingMaterials()
{
	//Checking if the dynamic material exists
	if (HexDynamicMaterial && (AlphaArray.Num() > 0 ) && (AlphaArray.Num() < 5))
	{
		//Assigning the alpha based on tile value
		HexDynamicMaterial->SetTextureParameterValue(NumberParamName, AlphaArray[TileValue]);

		//Assigning RGB Based on tile value
		switch (TileValue)
		{
			case 1: HexDynamicMaterial->SetVectorParameterValue(ColorParamName, FLinearColor(1, 0, 0, 1));
					break;
			case 2: HexDynamicMaterial->SetVectorParameterValue(ColorParamName, FLinearColor(0, 1, 0, 1));
					break;
			case 3: HexDynamicMaterial->SetVectorParameterValue(ColorParamName, FLinearColor(0, 0, 1, 1));
					break;
			default : HexDynamicMaterial->SetVectorParameterValue(ColorParamName, FLinearColor(0.5, 0.5, 0.5, 1));

		}
	}
}

void AHexGridMesh::UnlockMesh()
{
	CanMoveMesh = true;
}

bool AHexGridMesh::LockMesh()
{
	CanMoveMesh = false;
	
	//Returns true value if successfully locked the mesh onto hexgrid
	return true;
}

bool AHexGridMesh::GetMeshStatus()
{
	return CanMoveMesh;
}

void AHexGridMesh::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping Begins"));
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping actor is %s"), *OtherActor->GetName());
	}
}

