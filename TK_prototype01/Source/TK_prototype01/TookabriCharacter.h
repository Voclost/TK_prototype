// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TookabriCharacter.generated.h"

UCLASS()
class TK_PROTOTYPE01_API ATookabriCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATookabriCharacter();

	// Array of movement locations - 3 lanes to be placed in the level
	UPROPERTY(EditAnywhere, Categorey = Logic)
	TArray<class ATargetPoint*>TargetArray;

	// Character lane swap speed
	UPROPERTY(EditAnywhere, Categorey = Logic)
	float speed;

	// Audio component for obstacle hit sound
	UPROPERTY(EditAnywhere, Categorey = Sound)
	UAudioComponent* hitObstacleSound;

	// Audio component for coin pickup sound
	UPROPERTY(EditAnywhere, Categorey = Sound)
	UAudioComponent* dingSound;


protected:
	ATookabriCharacter();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ScoreUp();

	// Will handle moving the target location of Tookabri left and right
	void moveRight();
	void moveLeft();

	// Overlap functions to be used upon capsule component collision
	UFUNCTION()
	void myOnComponentOverlap(AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SwwepResult);

	UFUNCTION()
	void myOnComponentEndOverlap(AActor* otherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Camera Boom for maintaining camera distance to the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// Camera we will use as the target view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// Player score
	UPROPERTY(BlueprintReadOnly)
	int32 Score;


private:
	// Data for character lane positioning 
	short CurrentLocation;
	FVector DesiredLocation;
	bool bBeingPushed;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
