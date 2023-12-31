// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LOSTCharacter.generated.h"

UENUM(BlueprintType)
enum GridJumpOptions
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerHasDied);

UCLASS(Blueprintable)
class ALOSTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALOSTCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(BlueprintReadWrite)
	int32 HP = 2;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Death")
	void PlayerDeath();	

	UPROPERTY(BlueprintAssignable)
	FPlayerHasDied OnDeath;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UFUNCTION(BlueprintCallable)
	bool teleport(AActor* target, GridJumpOptions MovOpt);

	UFUNCTION(BlueprintCallable)
	bool isValidGridPosition(FVector pos);

};

