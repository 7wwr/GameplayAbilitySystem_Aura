// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Child/Aura.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

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

void AAura::InitAbilitySystem()
{
	//获取PlayerState
	ThisPlayerState = GetPlayerState();
	AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(ThisPlayerState);
	check(AuraPlayerState);	//相当于断言检测AuraPlayerState是否有效，无效则跳出
	//获取ASC组件
	AbilitySystemComponent = AuraPlayerState->AbilitySystemComponent;
	//初始化ASC组件
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
	//获取AS组件
	AttributeSet = AuraPlayerState->AttributeSet;
}

void AAura::InitHUDSystem()
{
	//GetController()获取的是AController类而不是APlayerController，所以需要转化，
	ThisPlayerController = Cast<APlayerController>(GetController());
	if (ThisPlayerController)	//涉及到多人游戏，只有本地有控制器，其他玩家的在本地只是个副本（获取时为空），如果不检查是否为空则会出现野指针现象
	{
		//这里是为了使用AAuraPlayerController类里面的initOverlay函数才转化的
		AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(ThisPlayerController);
		if(AuraPlayerController)	//同上一个if说明
		{
			AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
			if(AuraHUD)	//同上一个if
			{
				//初始化并添加到屏幕上（InitOverlay函数效果）
				AuraHUD->InitOverlay(ThisPlayerController,ThisPlayerState,AbilitySystemComponent,AttributeSet);
			}
		}
	}
	
}

void AAura::InitAnyNeeded()
{
	//这俩顺序不能错，因为InitHUDSystem()函数需要用到InitAbilitySystem()所获得的ASC，AS和PlayerState
	InitAbilitySystem();
	InitHUDSystem();
}

void AAura::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAnyNeeded();
}

void AAura::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAnyNeeded();
}
