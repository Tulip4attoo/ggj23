// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;


UCLASS()
class GGJ23_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// attached components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UCharacterMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComp;

	// currently, skill 1: magic projectile (more like normal attack lol)
	//            skill 2: black hole (more like an ulti)
	//            skill 3: teleport ball (it should be redesign like reaper teleport)
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> Skill1Class;

	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Skill")
		UAnimMontage* CastSkill1Anim;

	UPROPERTY(EditAnywhere, Category = "Skill")
		UAnimMontage* CastSkill2Anim;

	FTimerHandle TimerHandle;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	// movement
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump() override;
	void Dash();

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();

	// skill
	void CastSkill1();
	void CastSkill1_TimeElapsed();
	void CastSkill2();
	void CastSkill2_TimeElapsed();

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
