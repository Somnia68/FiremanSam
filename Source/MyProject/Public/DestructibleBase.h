// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "DestructibleBase.generated.h"

UCLASS()
class MYPROJECT_API ADestructibleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleBase();

	//Function used when something else hits the object (such as the Shoval Axe or something similar.)
	UFUNCTION(BlueprintCallable)
	void WeaponDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Trigger function will be used to find an overlapping with a specific trigger box.
	UFUNCTION(BlueprintCallable)
	void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	//Destroy will be called when the full damage has been taking and the object is destroyed. Causing Impact Damage and making it fall apart.
	UFUNCTION(BlueprintCallable)
	void Destroy(float Damage, FVector HitLocation, FVector ImpulseDirection, float Impulse);


	//Trigger box Setup.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
	class UBoxComponent* TriggerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Destructible)
	class UDestructibleComponent* DestructibleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	bool IsTriggerable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	bool IsDestroyed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float MaximumHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float DamageValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Destructible)
	float DefaultImpulse;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
