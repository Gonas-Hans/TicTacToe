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

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &ATTT_PlayerController::PlayerClick);
	
}

// Begin Play
void ATTT_PlayerController::BeginPlay()
{
	Super::BeginPlay();
		
	// Create grid by CellActor
    SpawnGrid();
	
}

// Tick
void ATTT_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bAIStep)
	{
		AIMakeClick();
	}
}

// Spawn grid by Cell actor
void ATTT_PlayerController::SpawnGrid()
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
    
    		SpawnedActor = GetWorld()->SpawnActor<AActor>(CellActor, FVector(XLocation, YLocation, 10.f),
    		FRotator(0.f, 0.f, 0.f));

			Grid.Add(SpawnedActor);
    	}
}

//Spawn sign, Cross or Zero
void ATTT_PlayerController::SpawnSign(AActor* CellForSpawn)
{
	if (SignActor)
	{
		FVector SpawnLoc = CellForSpawn->GetActorLocation()+ FVector(0.f, 0.f, 10.f);
		FRotator SpawnRot = CellForSpawn->GetActorRotation();
        		
        GetWorld()->SpawnActor<AActor>(SignActor, SpawnLoc, SpawnRot);
        
		Marked.Add(CellForSpawn);

		SwitchSign();
		SwitchAIBot();
	}
}

// Switch sign, cross to zero or zero to cross
void ATTT_PlayerController::SwitchSign()
{
	bToggle = !bToggle;
	
	if (bToggle)
		SignActor = CrossActor;
	else
		SignActor = ZeroActor;
}

// Turn on or turn off AI step
void ATTT_PlayerController::SwitchAIBot()
{
	bAIStep = !bAIStep;
}

// Player click
void ATTT_PlayerController::PlayerClick()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	//At first player choice sign. Until player makes a choice, the game will not start
	if (!SignActor)
		ChoiceSign(HitActor);
	
	// If player click on cell that
	if ((HitActor->GetClass() == CellActor))
	{
		//If cell is blank (Marked array doesn't have HitActor) that player can spawn sign Cross or Zero 
		if (Marked.Find(HitActor) == INDEX_NONE)
		{
			SpawnSign(HitActor);
		}
		//Find cell index in grid array
		int Index = 0;
		Grid.Find(HitActor, Index);
		UE_LOG(LogTemp, Warning, TEXT("%d"), Index);
	}
	
}

// AI make "click" for spawn sign
void ATTT_PlayerController::AIMakeClick()
{
	//int CellIndex = 0;
	//if (LineScore == 0)
	int CellIndex = FMath::RandRange(0, 8);

	AActor* HitActor = Grid[CellIndex];
	
	if (Marked.Find(HitActor) == INDEX_NONE)
	{
		SpawnSign(HitActor);
	}
}

// Choice sign or who first make step
void ATTT_PlayerController::ChoiceSign(AActor* Sign)
{
	if ((Sign->GetClass() == CrossActor))
	{
		bAIStep = false;
		SignActor = CrossActor;
	}

	if ((Sign->GetClass() == ZeroActor))
	{
		bAIStep = true;
		SignActor = CrossActor;
	}
}


	