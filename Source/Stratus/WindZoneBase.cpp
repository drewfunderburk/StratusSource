// Fill out your copyright notice in the Description page of Project Settings.


#include "WindZoneBase.h"
#include "WindZoneAffectable.h"

// Sets default values
AWindZoneBase::AWindZoneBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
}

// Called when the game starts or when spawned
void AWindZoneBase::BeginPlay()
{
	Super::BeginPlay();
	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &AWindZoneBase::OnBeginOverlap);
	CapsuleCollider->OnComponentEndOverlap.AddDynamic(this, &AWindZoneBase::OnEndOverlap);
}

// Called every frame
void AWindZoneBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> overlappingActors;
	CapsuleCollider->GetOverlappingActors(overlappingActors, AActor::StaticClass());
	for (AActor* actor : overlappingActors)
	{
		if (actor->Implements<UWindZoneAffectable>())
		{
			IWindZoneAffectable* windZoneAffectableActor = Cast<IWindZoneAffectable>(actor);
			windZoneAffectableActor->Execute_OnWindZoneStay(actor, this, Strength);
		}
	}
}

void AWindZoneBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->Implements<UWindZoneAffectable>())
	{
		IWindZoneAffectable* windZoneAffectableActor = Cast<IWindZoneAffectable>(OtherActor);
		windZoneAffectableActor->Execute_OnWindZoneEnter(OtherActor, this, Strength);
	}
}

void AWindZoneBase::OnEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UWindZoneAffectable>())
	{
		IWindZoneAffectable* windZoneAffectableActor = Cast<IWindZoneAffectable>(OtherActor);
		windZoneAffectableActor->Execute_OnWindZoneExit(OtherActor, this, Strength);
	}
}

#if WITH_EDITOR
void AWindZoneBase::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName propertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	if (propertyName == GET_MEMBER_NAME_CHECKED(AWindZoneBase, Radius))
	{
		if (CapsuleCollider)
			CapsuleCollider->SetCapsuleRadius(Radius);
		//ParticleSystem->SetFloatParameter(TEXT("Constant"), Radius);
	}
}
#endif