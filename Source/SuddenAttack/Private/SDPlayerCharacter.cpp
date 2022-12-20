// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPlayerCharacter.h"

// Sets default values
ASDPlayerCharacter::ASDPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//카메라 기본 셋팅
	SDCameracomponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SDCamera"));
	check(SDCameracomponent != nullptr);
	SDCameracomponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	SDCameracomponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	SDCameracomponent->bUsePawnControlRotation = true;

	SDFPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstMesh"));
	SDFPSMesh->SetOnlyOwnerSee(true);
	SDFPSMesh->SetupAttachment(SDCameracomponent);
	SDFPSMesh->bCastDynamicShadow = false;
	SDFPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

	bWalk = false;
}

// Called when the game starts or when spawned
void ASDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//AWSD를 이용한 플레이어 이동
	PlayerInputComponent->BindAxis("MoveForward", this, &ASDPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASDPlayerCharacter::MoveRight);

	//마우스 조작을 이용한 시야 움직임
	PlayerInputComponent->BindAxis("Turn", this, &ASDPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASDPlayerCharacter::AddControllerPitchInput);

	//점프
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASDPlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASDPlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &ASDPlayerCharacter::WalkingStart);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &ASDPlayerCharacter::WalkingStop);
}

//캐릭터의 앞뒤 움직임
void ASDPlayerCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	if (bWalk)
	{
		//걷기
		AddMovementInput(Direction, Value/2);
	}
	else
	{
		AddMovementInput(Direction, Value);
	}
}

//캐릭터의 양옆 움직임
void ASDPlayerCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (bWalk)
	{
		//걷기
		AddMovementInput(Direction, Value / 2);
	}
	else
	{
		AddMovementInput(Direction, Value);
	}
}

void ASDPlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void ASDPlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void ASDPlayerCharacter::WalkingStart()
{
	bWalk = true;
}

void ASDPlayerCharacter::WalkingStop()
{
	bWalk = false;
}

