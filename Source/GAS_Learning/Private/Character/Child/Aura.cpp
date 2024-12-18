// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Child/Aura.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAura::AAura()
{
	PrimaryActorTick.bCanEverTick = false;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->TargetArmLength = 500.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
