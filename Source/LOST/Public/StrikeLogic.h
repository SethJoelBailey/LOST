// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StrikeLogic.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOST_API UStrikeLogic : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStrikeLogic();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int32 CallTracker = 5;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Early Warning")
	void DisplayWarning();

private:
	UFUNCTION(BlueprintCallable)
	AActor* fireLightning();

	UFUNCTION(BlueprintCallable)
	void WhenToZap();

	UFUNCTION()
	void lightningTimer();
	FTimerHandle TimerHandle;

};
