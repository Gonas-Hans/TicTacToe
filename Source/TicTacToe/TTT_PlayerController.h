// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TTT_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATTT_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATTT_PlayerController();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> CellActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> CrossActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ZeroActor;

	UPROPERTY()
	TSubclassOf<AActor> AISign;
	
	UPROPERTY()
	TSubclassOf<AActor> PlayerSign;
	
	UPROPERTY()
	TArray<AActor*> AICells;

	UPROPERTY()
	TArray<AActor*> PlayerCells;
		
	UPROPERTY()
	TArray<AActor*> MarkedCells;

	UPROPERTY()
	TArray<AActor*> Grid;
	
	int PlayerScore = 0;
	void PlayerMakeClick();
	
	int AIScore = 0;
	bool bAICanStep = false;
	void AIMakeClick();
	void AICheckGrid();
	
	void SignSpawn(AActor* CellForSpawn, TSubclassOf<AActor> Sign, TArray<AActor*> &Cells, int &Score);
	void SignChoice(AActor* Sign);
	
	void GridSpawn(TSubclassOf<AActor> Cell, TArray<AActor*> &GridArray);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	virtual void SetupInputComponent() override;
	
	
};
