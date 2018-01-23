// Fill out your copyright notice in the Description page of Project Settings.

#include "TK_prototype01.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimBlueprint.h"
#include "Engine/TargetPoint.h"
#include "TK_prototype01GameModeBase.h"
#include "TookabriCharacter.h"


// Sets default values
ATookabriCharacter::ATookabriCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	UCapsuleComponent* GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	
}

// Called when the game starts or when spawned
void ATookabriCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATookabriCharacter::ScoreUp()
{
}

void ATookabriCharacter::moveRight()
{
}

void ATookabriCharacter::moveLeft()
{
}

void ATookabriCharacter::myOnComponentOverlap(AActor * otherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SwwepResult)
{
}

void ATookabriCharacter::myOnComponentEndOverlap(AActor * otherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ATookabriCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATookabriCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

