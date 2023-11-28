// Fill out your copyright notice in the Description page of Project Settings.


#include "Lightning.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"

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
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALightning::WhenToZap, 1.0f, false, 2.0f);
	// ...

}


// Called every frame
void ALightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

AActor* ALightning::fireLightning()
{
	RemoveWarning();
	FHitResult* hit = new FHitResult;
	FVector start = GetActorLocation() + FVector(50, -50, 600);
	FVector end = start + FVector(0, 0, -1000);
	GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility);
	if (hit)
	{
		DrawDebugLine(GetWorld(), start, hit->Location, FColor::Blue, false, 0.5f, 0, 10.0f);
		//DrawDebugSphere(GetWorld(), hit->Location, 50, 50, FColor::Blue, false, 0.5f);
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

	if (true)
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
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALightning::WhenToZap, 1.0f, false);
}

void ALightning::lightningTimer()
{

}

