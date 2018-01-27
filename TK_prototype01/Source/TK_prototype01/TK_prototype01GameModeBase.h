// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TK_prototype01GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TK_PROTOTYPE01_API ATK_prototype01GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	float gameSpeed;
	
		
public:
	ATK_prototype01GameModeBase();

	void CharScoreUp(unsigned int charScore);

	UFUNCTION()
	float GetInvGameSpeed();
	
	UFUNCTION()
	float GetGameSpeed();
	
	UFUNCTION()
	int32 GetGameLevel();


protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 numCoinsForSpeedIncrease;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float gameSpeedIncrease;

	UPROPERTY(BlueprintReadWrite)
	int32 gameLevel;

};
