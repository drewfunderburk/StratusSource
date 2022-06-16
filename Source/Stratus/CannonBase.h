// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleBase.h"
#include "CannonBase.generated.h"

/**
 * 
 */
UCLASS()
class STRATUS_API ACannonBase : public AModuleBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Cannon Base")
	void OnFire(const float delay);

	float GetRange() const { return range; }
	void SetRange(float newRange) { range = newRange; }

	float GetReloadSpeed() const { return ReloadSpeed; }
	void SetReloadSpeed(float newReloadSpeed) { ReloadSpeed = newReloadSpeed; }

	float GetProjectileSpeed() const { return projectileSpeed; }
	void SetProjectileSpeed(float newProjectileSpeed) { projectileSpeed = newProjectileSpeed; }

	float GetHorizontalAccuracyOffset() const { return horizontalAccuracyOffset; }
	void SetHorizontalAccuracyOffset(float newHorizontalAccuracy) { horizontalAccuracyOffset = newHorizontalAccuracy; }

	float GetVerticalAccuracyOffset() const { return verticalAccuracyOffset; }
	void SetVerticalAccuracyOffset(float newVerticalAccuracy) { verticalAccuracyOffset = newVerticalAccuracy; }

	bool GetIsFireReady() const { return isFireReady; }
	void SetIsFireReady(bool fireReady) { isFireReady = fireReady; }

	bool GetIsRightSide() const { return isRightSide; }
	void SetIsRightSide(bool rightSide) { isRightSide = rightSide; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	float range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	float ReloadSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	float projectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	float horizontalAccuracyOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	float verticalAccuracyOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	bool isFireReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cannon Base", meta = (AllowPrivateAccess = "true"))
	bool isRightSide;
};
