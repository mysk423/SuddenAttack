// Fill out your copyright notice in the Description page of Project Settings.


#include "SDPlayerCharacter.h"

// Sets default values
ASDPlayerCharacter::ASDPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ī�޶� �⺻ ����
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

	//AWSD�� �̿��� �÷��̾� �̵�
	PlayerInputComponent->BindAxis("MoveForward", this, &ASDPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASDPlayerCharacter::MoveRight);

	//���콺 ������ �̿��� �þ� ������
	PlayerInputComponent->BindAxis("Turn", this, &ASDPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASDPlayerCharacter::AddControllerPitchInput);

	//����
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASDPlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASDPlayerCharacter::StopJump);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &ASDPlayerCharacter::WalkingStart);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &ASDPlayerCharacter::WalkingStop);
}

//ĳ������ �յ� ������
void ASDPlayerCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	if (bWalk)
	{
		//�ȱ�
		AddMovementInput(Direction, Value/2);
	}
	else
	{
		AddMovementInput(Direction, Value);
	}
}

//ĳ������ �翷 ������
void ASDPlayerCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (bWalk)
	{
		//�ȱ�
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

