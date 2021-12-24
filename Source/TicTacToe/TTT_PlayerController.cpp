// Fill out your copyright notice in the Description page of Project Settings.


#include "TTT_PlayerController.h"

#include <string>

ATTT_PlayerController::ATTT_PlayerController()
{
	bToggle = true;
	
}

void ATTT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &ATTT_PlayerController::OnMouseClick);
	
}

void ATTT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create grid by CellActor
	SpawnGrid(CellActor);
	
}

void ATTT_PlayerController::OnMouseClick()
{
	TSubclassOf<AActor> SpawnSign;
	FHitResult HitResult;
	int32 Index = 0;
	
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);

	AActor* HitActor = HitResult.GetActor();
	
	if (Marked.Find(HitActor) == INDEX_NONE)
	{
		// If click on Cell that spawn cross or zero (toggle)
		if ((HitActor->GetClass() == CellActor))
		{
			if (bToggle)
			{
				SpawnSign = CrossActor;
				bToggle = false;
			}
			else
			{
				SpawnSign = ZeroActor;
				bToggle = true;
			}
		
			FVector SpawnLoc = HitActor->GetActorLocation()+ FVector(0.f, 0.f, 10.f);
			FRotator SpawnRot = HitActor->GetActorRotation();
		
			GetWorld()->SpawnActor<AActor>(SpawnSign, SpawnLoc, SpawnRot);

			Marked.Add(HitActor);
			
			Grid.Find(HitActor, Index);
			UE_LOG(LogTemp, Warning, TEXT("%d"), Index);
			
		}
	}
}

void ATTT_PlayerController::SpawnGrid(const TSubclassOf<AActor> GridCell)
{
	int Size = 3;
	float CellSpace = 150.f;
	float XLocation;
	float YLocation;
	AActor* SpawnedActor;
	
	for (int i = 0; i < 9; i++)
    	{
    		XLocation = (i % Size) * CellSpace;
    		YLocation = (i / Size) * CellSpace;
    
    		SpawnedActor = GetWorld()->SpawnActor<AActor>(GridCell, FVector(XLocation, YLocation, 10.f),
    		FRotator(0.f, 0.f, 0.f));

			Grid.Add(SpawnedActor);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *SpawnedActor->GetName());
		
    	}
}
/*GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));*/

