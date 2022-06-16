// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WindZoneBase.h"
#include "WindZoneAffectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWindZoneAffectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STRATUS_API IWindZoneAffectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Wind Zone Affectable")
	void OnWindZoneEnter(AWindZoneBase* source, float strength);

	UFUNCTION(BlueprintNativeEvent, Category = "Wind Zone Affectable")
	void OnWindZoneStay(AWindZoneBase* source, float strength);

	UFUNCTION(BlueprintNativeEvent, Category = "Wind Zone Affectable")
	void OnWindZoneExit(AWindZoneBase* source, float strength);
};
