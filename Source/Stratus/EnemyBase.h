// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UCLASS()
class STRATUS_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetHealth() const { return health; }

	UFUNCTION(BlueprintCallable)
	UPARAM(DisplayName = "Health") float TakeDamage(float damage);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Base", meta = (AllowPrivateAccess = "true"))
	float health = 1;
};
