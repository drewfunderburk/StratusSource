// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "WindZoneBase.generated.h"

UCLASS()
class STRATUS_API AWindZoneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWindZoneBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
#if	WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
#endif

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wind Zone Base", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wind Zone Base", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleSystem;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Zone Base")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Zone Base")
	float HalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind Zone Base")
	float Strength = 1;
};
