// Fill out your copyright notice in the Description page of Project Settings.


#include "TTT_PlayerController.h"

ATTT_PlayerController::ATTT_PlayerController()
{
	bToggle = true;

	
}

void ATTT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &ATTT_PlayerController::OnMouseClick);
	
}

void ATTT_PlayerController::OnMouseClick()
{
	TSubclassOf<AActor> SpawnSign;
	
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, HitResult);
	AActor* HitActor = HitResult.GetActor();
	
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
		
		GetWorld()->SpawnActor<AActor>(SpawnSign, HitActor->GetActorLocation() + FVector(0.f, 0.f, 10.f),
			HitActor->GetActorRotation());
		
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red,
			FString::Printf(TEXT("Mouse Click+++ Actor: %s"),
			*HitResult.GetActor()->GetName()));
	}
	
}

void ATTT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create grid by CellActor
	int Size = 3;
	float CellSpace = 150.f;
	float XLocation;
	float YLocation;
	
	for (int i = 0; i < 9; i++)
	{
		XLocation = (i % Size) * CellSpace;
		YLocation = (i / Size) * CellSpace;

		GetWorld()->SpawnActor<AActor>(CellActor, FVector(XLocation, YLocation, 10.f),
		FRotator(0.f, 0.f, 0.f));
		
		
	}
}
