// Copyright Epic Games, Inc. All Rights Reserved.

#include "LOSTCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ALOSTCharacter::ALOSTCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ALOSTCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool ALOSTCharacter::teleport(AActor* target, GridJumpOptions MovOpt)
{
	auto oneGrid = 100;
	FVector local = (target->GetActorLocation());

	if (target)
	{
		switch (MovOpt)
		{

		case Up:
			if (withinGameSpaceBounds(local.X, local.Y, MovOpt))
			{
				target->SetActorLocation(FVector(local.X + oneGrid,local.Y,local.Z));
			}
			break;

		case Down:
			if (withinGameSpaceBounds(local.X, local.Y, MovOpt))
			{
				target->SetActorLocation(FVector(local.X - oneGrid, local.Y, local.Z));
			}
			break;

		case Left:
			if (withinGameSpaceBounds(local.X, local.Y, MovOpt))
			{
				target->SetActorLocation(FVector(local.X, local.Y - oneGrid, local.Z));
			}
			break;

		case Right:
			if (withinGameSpaceBounds(local.X, local.Y, MovOpt))
			{
				target->SetActorLocation(FVector(local.X, local.Y + oneGrid, local.Z));
			}
			break;
		default:
			break;
		}
		
		return true;
	}
	return false;

	
}

bool ALOSTCharacter::withinGameSpaceBounds(float playerLocationX, float playerLocationY, GridJumpOptions direction, float top, float bottom, float farLeft, float farRight)
{
	switch (direction)
	{
	case Up:
		if (playerLocationX == top) return false;
		break;
	case Down:
		if (playerLocationX == bottom) return false;
		break;
	case Left:
		if (playerLocationY == farLeft) return false;
		break;
	case Right:
		if (playerLocationY == farRight) return false;
		break;
	default:
		break;
	}
	return true;
}
