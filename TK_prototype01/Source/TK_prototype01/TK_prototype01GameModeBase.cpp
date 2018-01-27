// Fill out your copyright notice in the Description page of Project Settings.

#include "TK_prototype01GameModeBase.h"




ATK_prototype01GameModeBase::ATK_prototype01GameModeBase()
{
	// set default pawn class to our ABountyDashCharacter
	DefaultPawnClass = ATK_prototype01GameModeBase::StaticClass();
	
	numCoinsForSpeedIncrease = 5;
	gameSpeed = 10.0f;
	gameSpeedIncrease = 5.0f;
	gameLevel = 1;
}

void ATK_prototype01GameModeBase::CharScoreUp(unsigned int charScore)
{
	if (charScore != 0 && charScore % numCoinsForSpeedIncrease == 0)
	{
		gameSpeed += gameSpeedIncrease;
		gameLevel++;
	}

}

float ATK_prototype01GameModeBase::GetInvGameSpeed()
{
	return -gameSpeed;
}

float ATK_prototype01GameModeBase::GetGameSpeed()
{
	return gameSpeed;
}

int32 ATK_prototype01GameModeBase::GetGameLevel()
{
	return gameLevel;
}
