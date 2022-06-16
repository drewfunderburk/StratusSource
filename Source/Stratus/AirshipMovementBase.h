// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirshipMovementBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STRATUS_API UAirshipMovementBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAirshipMovementBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Increases Speed Level by 1 up to its cap
	UFUNCTION(BlueprintCallable, Category = "Airship Movement Base")
	void IncreaseThrottle();

	// Decreases Speed Level by 1 down to zero
	UFUNCTION(BlueprintCallable, Category = "Airship Movement Base")
	void DecreaseThrottle();

	// Add yaw force (0 - 1 for best behavior)
	UFUNCTION(BlueprintCallable, Category = "Airship Movement Base")
	void AddYaw(float axisValue);

	// Add pitch force (0 - 1 for best behavior)
	UFUNCTION(BlueprintCallable, Category = "Airship Movement Base")
	void AddPitch(float axisValue);

private:
	// Update and apply thrust based on Speed Level
	void HandleThrust(float DeltaTime);

	// Constrain pitch
	void ConstrainPitch(float DeltaTime);

private:
	// Speed to use from speedlevelSpeeds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	int speedLevel = 1;

	// Speeds to apply as force
	// By default:
	// 0 - Reverse
	// 1 - Stopped
	// 2 - Slow
	// 3 - Medium
	// 4 - Full
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	TArray<float> speedLevelSpeeds = { 1, 0, 1, 2, 3 };

	// Value to multiply into the speed value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float speedLevelSpeedsForceMultiplier = 300000000.0f;

	// Force to apply towards yaw
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float yawForce = 1.0f;

	// Force to apply towards pitch
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float pitchForce = 1.0f;

	// Value to multiply into all rotational forces (yaw, pitch)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float rotationalForceMultiplier = 2000000000000.0f;
	
	// Minimum pitch angle to allow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float minimumPitchAngle = -40.0f;

	// Maximum pitch angle to allow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float maximumPitchAngle = 40.0f;

	// Angle shy of minimum or maximum pitch to begin soft clamping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Airship Movement", meta = (AllowPrivateAccess = "true"))
	float pitchTolerance = 10.0f;

private:
	// Reference to the owning actor's static mesh
	UStaticMeshComponent* staticMesh;
};
