// Fill out your copyright notice in the Description page of Project Settings.


#include "SDAiCharacter.h"

// Sets default values
ASDAiCharacter::ASDAiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASDAiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASDAiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

