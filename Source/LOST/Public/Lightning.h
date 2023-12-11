// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LOSTCharacter.generated.h"
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

	UFUNCTION()
	void PlayerHasDied();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Early Warning")
	void DisplayWarning();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Early Warning")
	void RemoveWarning();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Hit Player")
	void DamagePlayer(AActor* struckActor);

	UPROPERTY(BlueprintReadWrite)
	int intensity = 10;

	UPROPERTY(BlueprintReadWrite)
	bool isPlayerAlive = true;

	//UPROPERTY(BlueprintReadWrite)
	//int startX = 50;

	//UPROPERTY(BlueprintReadWrite)
	//int startY = -50;

	//UPROPERTY(BlueprintReadWrite)
	//int startZ = 600;

private:
	UFUNCTION(BlueprintCallable)
	AActor* fireLightning(int startX = 50, int startY = -50, int startZ = 600, int endX = 0, int endY = 0, int endZ = -1000);

	UFUNCTION(BlueprintCallable)
	void fireFireLightning();

	UFUNCTION(BlueprintCallable)
	void WhenToZap();

	UFUNCTION()
	void lightningTimer();
	FTimerHandle TimerHandle;
	FTimerHandle DestinedZap;

	
};
