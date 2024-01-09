// Fill out your copyright notice in the Description page of Project Settings.


#include "Lightning.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
ALightning::ALightning()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	// ...
}


// Called when the game starts
void ALightning::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALightning::WhenToZap, (FMath::RandRange(1.0f, 1.5f)), false, 2.0f);
//	ALOSTCharacter* AsALOSTCharacter = Cast<ALOSTCharacter>(UGameplayStatics::GetPlayerCharacter(0));
//	AsALOSTCharacter->OnDeath.AddDynamic(this, &Lightning::PlayerHasDied);
	// ...

}

void ALightning::PlayerHasDied()
{
}


// Called every frame
void ALightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

AActor* ALightning::fireLightning(int startX, int startY, int startZ, int endX, int endY, int endZ)
{
	RemoveWarning();
	FHitResult* hit = new FHitResult;
	FVector start = GetActorLocation() + FVector(startX, startY, startZ);
	FVector end = start + FVector(endX, endY, endZ);
	GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility);
	if (hit)
	{
		DrawDebugLine(GetWorld(), start, hit->Location, FColor(0, 0, 0));
	}
	else
	{
		DrawDebugLine(GetWorld(), start, hit->Location, FColor(100, 0, 0));

	}
	AActor* hitObject = hit->GetActor();
	DamagePlayer(hitObject);
	return hitObject;
}

void ALightning::fireFireLightning()
{
	fireLightning();
}


void ALightning::WhenToZap()
{
	
	CallTracker--;

	if (isPlayerAlive)
	{
		int zap = FMath::RandRange(1, intensity);
		if (zap == 1)
		{
			intensity--;
			if (intensity <= 1) intensity = 2;
			DisplayWarning();
			GetWorld()->GetTimerManager().SetTimer(DestinedZap, this, &ALightning::fireFireLightning, 0.5f, false);
		}
		else
		{
			CallTracker = 5;
		}
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALightning::WhenToZap, (FMath::RandRange(1.0f, 1.5f)) , false);
	}
	
}

void ALightning::lightningTimer()
{

}

