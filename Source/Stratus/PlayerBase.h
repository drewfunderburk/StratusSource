// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "AirshipMovementBase.h"
#include "CannonBase.h"

#include "PlayerBase.generated.h"

UCLASS()
class STRATUS_API APlayerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnCameraPitch(float value);
	void OnCameraYaw(float value);
	void OnCameraZoom(float value);
	void OnPitch(float value);
	void OnYaw(float value);
	void OnIncreaseThrottle();
	void OnDecreaseThrottle();
	void OnFrontAbility();
	void OnBackAbility();
	void OnFire();
	void OnPause();

	UStaticMeshComponent* GetStaticMesh() { return staticMesh; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float mouseSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	bool invertY = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float cameraZoomScale = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	bool cameraCanZoom = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float minimumCameraZoom = 3500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float maximumCameraZoom = 20000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float cameraZoomLerpSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float cameraZoomTargetDistance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector cameraZoomTargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Base", meta = (AllowPrivateAccess = "true"))
	float health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Movement", meta = (AllowPrivateAccess = "true"))
	UAirshipMovementBase* airshipMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* staticMesh;

private:
	USpringArmComponent* cameraBoom;
};
