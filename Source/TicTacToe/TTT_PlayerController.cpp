// Fill out your copyright notice in the Description page of Project Settings.


#include "TTT_PlayerController.h"

#include "LevelEditorMenuContext.h"
#include "Kismet/KismetSystemLibrary.h"


// Constructor
ATTT_PlayerController::ATTT_PlayerController()
{
	GridWeight.Init(0, 9);
	
}

// Inputs
void ATTT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &ATTT_PlayerController::PlayerMakeClick);
	
}

// Begin Play
void ATTT_PlayerController::BeginPlay()
{
	Super::BeginPlay();
		
	// Create grid by CellActor
    GridSpawn(CellActor);
	
}

// Tick
void ATTT_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bAICanStep)
	{
		AIMakeClick();
	}
	
	int Item = 0;
	if (GridWeight.Find(Item) == INDEX_NONE)
		UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit,
		true);
	
}

// Spawn grid by Cell actor
void ATTT_PlayerController::GridSpawn(TSubclassOf<AActor> Cell)
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

			UE_LOG(LogTemp, Warning, TEXT("Grid X %f Y %f"), XLocation, YLocation);
    
    		SpawnedActor = GetWorld()->SpawnActor<AActor>(Cell, FVector(XLocation, YLocation, 10.f),
    		FRotator(0.f, 0.f, 0.f));

			GridCells.Add(SpawnedActor);
    	}
}

// Player click
void ATTT_PlayerController::PlayerMakeClick()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	//At first player choice sign. Until player makes a choice, the game will not start
	if (!PlayerSign)
		SignChoice(HitActor);
	
	// If player click on cell that
	if ((HitActor->GetClass() == CellActor))
	{
		SignSpawn(HitActor, PlayerSign, -1);
	}
}

// AI make "click" for spawn sign
void ATTT_PlayerController::AIMakeClick()
{
	int CellIndex = FMath::RandRange(0, 8);
		
	AActor* HitActor = GridCells[CellIndex];
		
	SignSpawn(HitActor, AISign, 1);
	
}

//Spawn sign, Cross or Zero
void ATTT_PlayerController::SignSpawn(AActor* HitActor, TSubclassOf<AActor> Sign, const int Weight)
{
	if (Sign)
	{
		//Find index of cell where sign will be spawn
     	int Index = 0;
     	GridCells.Find(HitActor, Index);
		
		//If cell is blank (weight == 0) that spawn sign 
		if (GridWeight[Index] == 0)
		{
			FVector SpawnLoc = HitActor->GetActorLocation()+ FVector(0.f, 0.f, 10.f);
			FRotator SpawnRot = HitActor->GetActorRotation();
                    		
			GetWorld()->SpawnActor<AActor>(Sign, SpawnLoc, SpawnRot);

			GridWeight[Index] = Weight;
			
			bAICanStep = !bAICanStep;
		}
		UE_LOG(LogTemp, Warning, TEXT("Grid points %d"), GridWeight[Index]);
	}
}
void ATTT_PlayerController::AICheckGrid()
{
	int Col = 0; // Column
	int Row = 0;
	// Check rows
	for (int i = 0; i < 3; ++i)
	{
		int RowSum = GridWeight[i*3] + GridWeight[i*3+1] + GridWeight[i*3+2];
	}
}



// Choice sign or who first make step
void ATTT_PlayerController::SignChoice(AActor* Sign)
{
	if ((Sign->GetClass() == CrossActor))
	{
		bAICanStep = false;
		PlayerSign = CrossActor;
		AISign = ZeroActor;
	}

	if ((Sign->GetClass() == ZeroActor))
	{
		bAICanStep = true;
		AISign= CrossActor;
		PlayerSign  = ZeroActor;
	}
}


	