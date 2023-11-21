// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lightning.generated.h"

UCLASS()
class LOST_API ALightning : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	ALightning();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int32 CallTracker = 5;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Early Warning")
	void DisplayWarning();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Early Warning")
	void RemoveWarning();

private:
	UFUNCTION(BlueprintCallable)
	AActor* fireLightning();

	UFUNCTION(BlueprintCallable)
	void fireFireLightning();

	UFUNCTION(BlueprintCallable)
	void WhenToZap();

	UFUNCTION()
	void lightningTimer();
	FTimerHandle TimerHandle;
	FTimerHandle DestinedZap;

};
