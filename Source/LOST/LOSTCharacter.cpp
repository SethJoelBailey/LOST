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
	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

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
	//PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bStartWithTickEnabled = true;
}

void ALOSTCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool ALOSTCharacter::teleport(AActor* target, GridJumpOptions MovOpt)
{
	if (!target)
		return false;

	auto oneGrid = 100;
	FVector local = (target->GetActorLocation());

	switch (MovOpt)
	{
	case Up:
		local.X += oneGrid;
		break;
	case Down:
		local.X -= oneGrid;
		break;
	case Left:
		local.Y -= oneGrid;
		break;
	case Right:
		local.Y += oneGrid;
		break;
	default:
		break;
	}

	if (isValidGridPosition(local))
	{
		target->SetActorLocation(local);
		return true;
	}
		
	return false;
	
}


bool ALOSTCharacter::isValidGridPosition(FVector pos)
{
	float top = 1750;
	float bottom = 1150;
	float farLeft = 1550;
	float farRight = 2150;

	if (pos.X > top || pos.X < bottom)
	{
		return false;
	}

	if (pos.Y < farLeft || pos.Y > farRight)
	{
		return false;
	}
		
	return true;

}
