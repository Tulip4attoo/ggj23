// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	MovementComp = GetCharacterMovement();

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

}


// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// just movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMainCharacter::Dash);

	// attack
	// PlayerInputComponent->BindAction("NormalAttack", IE_Pressed, this, &AMainCharacter::NormalAttack);

	// skill
	PlayerInputComponent->BindAction("CastSkill1", IE_Pressed, this, &AMainCharacter::CastSkill1);
	PlayerInputComponent->BindAction("CastSkill2", IE_Pressed, this, &AMainCharacter::CastSkill2);

	// change equipment
	// PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMainCharacter::PrimaryInteract);

}


// Movement part
void AMainCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}


void AMainCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}


void AMainCharacter::Jump()
{
	Super::Jump();
}


void AMainCharacter::Dash()
{
}


// skill part
void AMainCharacter::CastSkill1()
{
	DisableInput(PlayerController);
	PlayAnimMontage(CastSkill1Anim);
	MovementComp->SetMovementMode(MOVE_None);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::CastSkill1_TimeElapsed, 0.25f);
}


void AMainCharacter::CastSkill2()
{
	PlayAnimMontage(CastSkill2Anim);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::CastSkill2_TimeElapsed, 0.25f);
}


void AMainCharacter::CastSkill1_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("RightHandMiddle1Socket");
	
	FTransform SpawnTM = FTransform(GetActorRotation(), HandLocation);
	// FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(Skill1Class, SpawnTM, SpawnParams);
	EnableInput(PlayerController);
	MovementComp->SetMovementMode(MOVE_Walking);
}


void AMainCharacter::CastSkill2_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("RightHandMiddle1Socket");
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(Skill1Class, SpawnTM, SpawnParams);
}
