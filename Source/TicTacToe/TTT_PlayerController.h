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
	TSubclassOf<AActor> SignActor;

	UPROPERTY()
	int LineScore;
	
	UPROPERTY()
	TArray<AActor*> Marked;

	UPROPERTY()
	TArray<AActor*> Grid;
	
	UFUNCTION()
	virtual void PlayerClick();

	UFUNCTION()
	void ChoiceSign(AActor* Sign);
	
	UFUNCTION()
	virtual void AIMakeClick();

	UFUNCTION()
	void SwitchSign();

	UFUNCTION()
	void SwitchAIBot();

	UFUNCTION()
	void SpawnSign(AActor* CellForSpawn);

	UFUNCTION()
	void SpawnGrid();
	
	bool bToggle = true;
	bool bAIStep = false;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	virtual void SetupInputComponent() override;
	
	
};
