// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"
#include "SDPlayerCharacter.generated.h"

UCLASS()
class SUDDENATTACK_API ASDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASDPlayerCharacter();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* SDCameracomponent;

	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* SDFPSMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//함수부분
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void WalkingStart();

	UFUNCTION()
	void WalkingStop();

	//변수 부분
public:
	bool bWalk;
};
