// Fill out your copyright notice in the Description page of Project Settings.


#include "AirshipMovementBase.h"

// GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, FString::Printf(TEXT("%s"), *staticMesh->GetRelativeRotation().ToString()));


// Sets default values for this component's properties
UAirshipMovementBase::UAirshipMovementBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAirshipMovementBase::BeginPlay()
{
	Super::BeginPlay();
	// Get owner static mesh
	staticMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (!staticMesh)
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::Printf(TEXT("Could not get Static Mesh")));

}

void UAirshipMovementBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Force zero roll
	if (!staticMesh) return;
	FRotator rotation = staticMesh->GetRelativeRotation();
	rotation.Roll = 0;
	staticMesh->SetRelativeRotation(rotation);

	HandleThrust(DeltaTime);
	ConstrainPitch(DeltaTime);
}

void UAirshipMovementBase::IncreaseThrottle()
{
	if (speedLevel + 1 < speedLevelSpeeds.Num())
		speedLevel++;
}

void UAirshipMovementBase::DecreaseThrottle()
{
	if (speedLevel - 1 >= 0)
		speedLevel--;
}

void UAirshipMovementBase::AddYaw(float axisValue)
{
	if (!staticMesh) return;
	staticMesh->AddTorqueInRadians(FVector(0, 0, axisValue * yawForce * rotationalForceMultiplier));
}

void UAirshipMovementBase::AddPitch(float axisValue)
{
	if (!staticMesh) return;
	//FVector rotation = staticMesh->GetOwner()->GetActorRotation().RotateVector(FVector(0, axisValue * pitchForce * rotationalForceMultiplier, 0));
	FVector yRotation = FVector(0, axisValue * pitchForce * rotationalForceMultiplier, 0);

	FVector rotation = GetOwner()->GetActorTransform().TransformPosition(yRotation);
	staticMesh->AddTorqueInRadians(rotation);
}

void UAirshipMovementBase::HandleThrust(float DeltaTime)
{
	if (!staticMesh) return;
	FVector force = staticMesh->GetOwner()->GetActorForwardVector();
	if (speedLevelSpeeds.IsValidIndex(speedLevel))
		force *= speedLevelSpeeds[speedLevel] * speedLevelSpeedsForceMultiplier;
	
	// Invert force if speedlevel is 0 (reverse)
	if (speedLevel < 1)
		force *= -1;

	staticMesh->AddForce(force);
}

void UAirshipMovementBase::ConstrainPitch(float DeltaTime)
{
	if (!staticMesh) return;
	FRotator rotation = staticMesh->GetRelativeRotation();

	// Hard clamp
	if (rotation.Pitch > maximumPitchAngle)
		staticMesh->SetRelativeRotation(FRotator(maximumPitchAngle, rotation.Yaw, rotation.Roll));
	else if (rotation.Pitch < minimumPitchAngle)
		staticMesh->SetRelativeRotation(FRotator(minimumPitchAngle, rotation.Yaw, rotation.Roll));

	// Soft Clamp by applying greater countering force the more pitchTolerance is exceeded
	if (rotation.Pitch > maximumPitchAngle - pitchTolerance)
	{
		float softLimit = maximumPitchAngle - pitchTolerance;
		float pitchOverLimit = rotation.Pitch - softLimit;
		AddPitch(FMath::Clamp<float>(pitchOverLimit, 0, 1));
	}
	else if (rotation.Pitch < minimumPitchAngle + pitchTolerance)
	{
		float softLimit = minimumPitchAngle + pitchTolerance;
		float pitchOverLimit = rotation.Pitch - softLimit;
		AddPitch(FMath::Clamp<float>(-pitchOverLimit, 0, -1));
	}
}

