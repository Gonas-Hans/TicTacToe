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

	UFUNCTION()
	virtual void SetupInputComponent() override;

	UFUNCTION()
	virtual void OnMouseClick();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> CellActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> CrossActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> ZeroActor;

	UPROPERTY()
	TArray<AActor*> Marked;

	UPROPERTY()
	TArray<AActor*> Grid;
	
	bool bToggle;
	
	void SpawnGrid(TSubclassOf<AActor> GridCell);

protected:
	virtual void BeginPlay() override;
	
};
