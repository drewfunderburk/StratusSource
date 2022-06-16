// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

APlayerBase::APlayerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	// Get BP components
	cameraBoom = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
	if (!cameraBoom) 
		UE_LOG(LogTemp, Error, TEXT("cameraBoom not found"));
	cameraZoomTargetDistance = cameraBoom->TargetArmLength;

	staticMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (!staticMesh)
		UE_LOG(LogTemp, Error, TEXT("staticMesh not found"));

	airshipMovement = Cast<UAirshipMovementBase>(GetComponentByClass(UAirshipMovementBase::StaticClass()));
	if (!airshipMovement)
		UE_LOG(LogTemp, Error, TEXT("airshipMovement not found"));

	cameraZoomTargetLocation = cameraBoom->GetRelativeLocation();
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensure cameraBoom is valid
	if (!cameraBoom) return;

	// Reset camera roll
	FRotator cameraRotation = cameraBoom->GetRelativeRotation();
	cameraRotation.Roll = 0.0f;
	cameraBoom->SetRelativeRotation(cameraRotation);

	// Lerp cameraBoom arm length towards cameraZoomTargetDistance
	if (FMath::Abs(cameraBoom->TargetArmLength - cameraZoomTargetDistance) > 0.1f)
	{
		cameraBoom->TargetArmLength = FMath::Lerp(cameraBoom->TargetArmLength, cameraZoomTargetDistance, cameraZoomLerpSpeed * DeltaTime);
	}
	else
		cameraBoom->TargetArmLength = cameraZoomTargetDistance;

	// Lerp cameraBoom relative location towards cameraZoomTargetLocation
	if ((cameraBoom->GetRelativeLocation() - cameraZoomTargetLocation).Size() > 0.1f)
	{
		cameraBoom->SetRelativeLocation(FMath::Lerp(cameraBoom->GetRelativeLocation(), cameraZoomTargetLocation, cameraZoomLerpSpeed * DeltaTime));
	}
	else
		cameraBoom->SetRelativeLocation(cameraZoomTargetLocation);
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Camera Pitch", this, &APlayerBase::OnCameraPitch);
	InputComponent->BindAxis("Camera Yaw", this, &APlayerBase::OnCameraYaw);
	InputComponent->BindAxis("Camera Zoom", this, &APlayerBase::OnCameraZoom);
	InputComponent->BindAxis("Pitch", this, &APlayerBase::OnPitch);
	InputComponent->BindAxis("Yaw", this, &APlayerBase::OnYaw);
	InputComponent->BindAction("Increase Throttle", IE_Pressed, this, &APlayerBase::OnIncreaseThrottle);
	InputComponent->BindAction("Decrease Throttle", IE_Pressed, this, &APlayerBase::OnDecreaseThrottle);
	InputComponent->BindAction("Front Ability", IE_Pressed, this, &APlayerBase::OnFrontAbility);
	InputComponent->BindAction("Back Ability", IE_Pressed, this, &APlayerBase::OnBackAbility);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerBase::OnFire);
	InputComponent->BindAction("Pause", IE_Pressed, this, &APlayerBase::OnPause);
}

void APlayerBase::OnCameraPitch(float value)
{
	if (!cameraBoom) return;
	FRotator rotation = FRotator::ZeroRotator;
	rotation.Pitch = value * mouseSensitivity;
	cameraBoom->AddLocalRotation(rotation);}

void APlayerBase::OnCameraYaw(float value)
{
	if (!cameraBoom) return;
	FRotator rotation = FRotator::ZeroRotator;
	rotation.Yaw = value * mouseSensitivity;
	cameraBoom->AddLocalRotation(rotation);
}

void APlayerBase::OnCameraZoom(float value)
{
	if (!cameraBoom) return;
	if (!cameraCanZoom) return;

	float newTargetDistance = cameraZoomTargetDistance + (value * cameraZoomScale);
	cameraZoomTargetDistance = FMath::Clamp(newTargetDistance, minimumCameraZoom, maximumCameraZoom);
}

void APlayerBase::OnPitch(float value)
{
	if (airshipMovement)
		airshipMovement->AddPitch(value);
}

void APlayerBase::OnYaw(float value)
{
	if (airshipMovement)
		airshipMovement->AddYaw(value);
}

void APlayerBase::OnIncreaseThrottle()
{
	airshipMovement->IncreaseThrottle();
}

void APlayerBase::OnDecreaseThrottle()
{
	airshipMovement->DecreaseThrottle();
}

void APlayerBase::OnFrontAbility()
{
}

void APlayerBase::OnBackAbility()
{
}

void APlayerBase::OnFire()
{
}

void APlayerBase::OnPause()
{
}

