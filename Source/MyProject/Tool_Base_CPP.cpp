// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool_Base_CPP.h"

// Sets default values
ATool_Base_CPP::ATool_Base_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATool_Base_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATool_Base_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
