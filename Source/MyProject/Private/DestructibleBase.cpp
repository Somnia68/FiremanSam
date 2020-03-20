// Fill out your copyright notice in the Description page of Project Settings.



#include "engine.h"
#include "DestructibleBase.h"

// Sets default values
ADestructibleBase::ADestructibleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));

	DestructibleComponent->SetupAttachment(RootComponent);
	//SImulate Generate Hit Events is also known as SetNotifyRigidBodyCollision
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerComponent->SetupAttachment(RootComponent);

	IsTriggerable = false;
	IsDestroyed = false;

	MaximumHealth = 10.f;

	DamageValue = 10.f;

	DefaultImpulse = 5.f;

}



// Called when the game starts or when spawned
void ADestructibleBase::BeginPlay()
{
	Super::BeginPlay();

	DestructibleComponent->OnComponentHit.AddDynamic(this, &ADestructibleBase::WeaponDamage);

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleBase::Trigger);

	CurrentHealth = MaximumHealth;
	
}

// Called every frame
void ADestructibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleBase::WeaponDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-10, 3.f, FColor::Blue, __FUNCTION__);
	GEngine->AddOnScreenDebugMessage(-9, 3.f, FColor::Blue, (!IsDestroyed && OtherComp->ComponentHasTag("Weapon")) ? "True" : "False");

	//MUST TAG THE WEAPON AS A WEAPON TO GET DESTRUCTIBLE MESH!
	if (!IsDestroyed && OtherComp->ComponentHasTag("Weapon"))
	{
		
		CurrentHealth = CurrentHealth - DamageValue;
			if (CurrentHealth <= 0.f) {
				Destroy(DamageValue, Hit.Location, NormalImpulse, DefaultImpulse);
			}
	}

}

void ADestructibleBase::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-8, 5.f, FColor::Blue, __FUNCTION__);
	GEngine->AddOnScreenDebugMessage(-5, 3.f, FColor::Blue, (!IsDestroyed && IsTriggerable && OtherActor->ActorHasTag("Player")) ? "True" : "False");
	//Player MUST BE TAGGED TO REGISTER THE TRIGGER BOX
	if (!IsDestroyed && IsTriggerable && OtherActor->ActorHasTag("Player")) {
		Destroy(DamageValue, DestructibleComponent->GetComponentLocation(), DestructibleComponent->GetForwardVector(), DefaultImpulse);
	}
}

void ADestructibleBase::Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse)
{
	GEngine->AddOnScreenDebugMessage(-2, 5.f, FColor::Blue, __FUNCTION__);
	if (!IsDestroyed) 
	{
		IsDestroyed = true;

		DestructibleComponent->ApplyDamage(Damage, HitLocation, ImpulseDir, Impulse);

	}

}