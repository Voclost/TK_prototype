// Fill out your copyright notice in the Description page of Project Settings.

#include "TookabriCharacter.h"
#include "TK_prototype01.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimBlueprint.h"
#include "EngineUtils.h"


// Sets default values
ATookabriCharacter::ATookabriCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(42.f, 96.0f);
	
	ConstructorHelpers::FObjectFinder<UAnimBlueprint>myAnimBP(TEXT("/Game/Character/Mannequin/Animations/BH_Character_AnimBP.BH_Character_AnimBP"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> myMesh(TEXT("/Game/Character/Mesh/SK_Mannequin.SK_Mannequin"));

	if (myMesh.Succeeded() && myAnimBP.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(myMesh.Object);
		GetMesh()->SetAnimInstanceClass(myAnimBP.Object->GeneratedClass);
	}

	// Rotate and position the mesh so it sits in the capsule component properly
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f,-GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Configure character movement
	GetCharacterMovement()->JumpZVelocity = 1450.0f;
	GetCharacterMovement()->GravityScale = 4.5f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	check(CameraBoom);

	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// The camera follows at this distance behind the character
	CameraBoom->TargetArmLength = 500.0f;

	// Offset to player
	CameraBoom->AddRelativeLocation(FVector(0.0f, 0.0f, 160.0f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	check(FollowCamera);

	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);

	// Rotational change to make the camera look down slightly
	FollowCamera->RelativeRotation = FRotator(-10.0f, 0.0f, 0.0f);

	// Game Properties
	CharSpeed = 10.0f;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATookabriCharacter::myOnComponentOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ATookabriCharacter::myOnComponentEndOverlap);

	// Poses the input at ID 0 (the default controller)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATookabriCharacter::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<ATargetPoint>TargetIter(GetWorld()); 
		TargetIter;
		++TargetIter)
	{
		TargetArray.Add(*TargetIter);
	}
	
	auto SortPred = [](const AActor& A, const AActor& B)->bool
	{
		return(A.GetActorLocation().Y < B.GetActorLocation().Y);
	};
	TargetArray.Sort(SortPred);

	CurrentLocation = ((TargetArray.Num() / 2) + (TargetArray.Num() % 2) - 1);

}

void ATookabriCharacter::ScoreUp()
{
}

void ATookabriCharacter::MoveRight()
{
	if ((Controller != nullptr))
	{
		if (CurrentLocation < TargetArray.Num() - 1)
		{
			++CurrentLocation;
		}
		else
		{
			// Do Nothing
		}
	}

}

void ATookabriCharacter::MoveLeft()
{
	if ((Controller != nullptr))
	{
		if (CurrentLocation > 0)
		{
			--CurrentLocation;
		}
		else
		{
			// Do Nothing
		}
	}

}


//UPrimitiveComponent* ThisActor, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex
void ATookabriCharacter::myOnComponentOverlap(UPrimitiveComponent* ThisActor, AActor * otherActor,
												UPrimitiveComponent * OtherComp, 
												int32 OtherBodyIndex,
												bool bFromSweep, const FHitResult & SwwepResult)
{

}

void ATookabriCharacter::myOnComponentEndOverlap(UPrimitiveComponent* ThisActor, AActor * otherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ATookabriCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Super::Tick(DeltaTime);
	if (TargetArray.Num() > 0)
	{
		FVector targetLoc = TargetArray[CurrentLocation] ->GetActorLocation();
		targetLoc.Z = GetActorLocation().Z;
		targetLoc.X = GetActorLocation().X;
		if (targetLoc != GetActorLocation())
		{
			SetActorLocation(FMath::Lerp(GetActorLocation(), targetLoc, CharSpeed
				* DeltaTime));
		}
	}


}

// Called to bind functionality to input
void ATookabriCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("MoveRight", IE_Pressed, this, &ATookabriCharacter::MoveRight);

	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &ATookabriCharacter::MoveLeft);


}

