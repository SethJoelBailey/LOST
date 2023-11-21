// Fill out your copyright notice in the Description page of Project Settings.


#include "StrikeLogic.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UStrikeLogic::UStrikeLogic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStrikeLogic::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UStrikeLogic::WhenToZap, 1.0f, true, 2.0f);
	DisplayWarning();
	// ...
	
}


// Called every frame
void UStrikeLogic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UStrikeLogic::fireLightning()
{

	FHitResult* hit = new FHitResult;
	FVector start = (GetOwner()->GetActorLocation() + FVector(50, -50, 600));
	FVector end = start + FVector(0, 0, -1000);
	GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_Visibility);
	if (hit)
	{
		DrawDebugLine(GetWorld(), start, hit->Location, FColor::Red, false, 0.5f, 0, 10.0f);
		DrawDebugSphere(GetWorld(), hit->Location, 50, 50, FColor::Blue, false, 0.5f);
	}
	else
	{
		DrawDebugLine(GetWorld(), start, hit->Location, FColor(100, 0, 0));
		
	}
	AActor* hitObject = hit->GetActor();
	return hitObject;
}


void UStrikeLogic::WhenToZap()
{
	int intenisty = 6;
	CallTracker--;

	if (CallTracker > 1)
	{
		int zap = FMath::RandRange(1, intenisty);
		if (zap == 1)
		{
			DisplayWarning();
			fireLightning();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Fire"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hold"));
			CallTracker = 5;
		}
	}
}

void UStrikeLogic::lightningTimer()
{

}


