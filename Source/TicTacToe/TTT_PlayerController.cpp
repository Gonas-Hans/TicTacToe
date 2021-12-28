// Fill out your copyright notice in the Description page of Project Settings.


#include "TTT_PlayerController.h"


// Constructor
ATTT_PlayerController::ATTT_PlayerController()
{
	
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
    GridSpawn(CellActor, Grid);
	
}

// Tick
void ATTT_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bAICanStep)
	{
		AIMakeClick();
	}
}

// Spawn grid by Cell actor
void ATTT_PlayerController::GridSpawn(TSubclassOf<AActor> Cell, TArray<AActor*> &GridArray)
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
    
    		SpawnedActor = GetWorld()->SpawnActor<AActor>(Cell, FVector(XLocation, YLocation, 10.f),
    		FRotator(0.f, 0.f, 0.f));

			GridArray.Add(SpawnedActor);
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
		SignSpawn(HitActor, PlayerSign, PlayerCells, PlayerScore);
		
		//Find cell index in grid array
		int Index = 0;
		Grid.Find(HitActor, Index);
		UE_LOG(LogTemp, Warning, TEXT("%d"), Index);
	}
}

// AI make "click" for spawn sign
void ATTT_PlayerController::AIMakeClick()
{
	
	//if (AIScore == 0)
	//{
		int CellIndex = FMath::RandRange(0, Grid.Num()-1);
		
		AActor* HitActor = Grid[CellIndex];
		
		SignSpawn(HitActor, AISign, AICells, AIScore);
		
	//}
}

void ATTT_PlayerController::AICheckGrid()
{
	for (int i = 0; i <9; ++i)
	{
		
		
	}
}

//Spawn sign, Cross or Zero
void ATTT_PlayerController::SignSpawn(AActor* CellForSpawn, TSubclassOf<AActor> Sign, TArray<AActor*> &Cells, int &Score)
{
	if (Sign)
	{
		//If cell is blank (Marked array doesn't have CellForSpawn) that player can spawn sign Cross or Zero 
		if (!(Grid.Find(CellForSpawn) == INDEX_NONE))
		{
			FVector SpawnLoc = CellForSpawn->GetActorLocation()+ FVector(0.f, 0.f, 10.f);
			FRotator SpawnRot = CellForSpawn->GetActorRotation();
                    		
			GetWorld()->SpawnActor<AActor>(Sign, SpawnLoc, SpawnRot);
                    
			Cells.Add(CellForSpawn);
			Grid.Remove(CellForSpawn);
			
			Score++;
			UE_LOG(LogTemp, Warning, TEXT("%d"), Score);
			
			bAICanStep = !bAICanStep;
		}
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


	