// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;	//网络复制
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); //检查AuraContext是否有效，在蓝图中设定
	
	//获取EnhancedInputLocalPlayerSubsystem
	UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if(Subsystem)	//涉及到多人游戏，只有本地的控制器有该系统，其他玩家的在本地只是个副本（获取时为空），如果不检查是否为空则会出现野指针现象
	{
		Subsystem->AddMappingContext(AuraContext,0);	//设置优先级
	}

	bShowMouseCursor = true;	//是否显示鼠标光标
	DefaultMouseCursor = EMouseCursor::Default;		//鼠标光标种类，比如箭形或手形

	FInputModeGameAndUI InputModeData;	
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::MoveFunction);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit)//是否有指向的物体（包括没有IEnemyInterface接口的actor,指向的是虚无，其实是怕敌人在地图边缘，光标向旁边一移就指向虚无了，这种情况非常少见（因为会设计空气墙），但存在），如果没有
	{
		if(ThisActor != nullptr)	//首先清除上一个物体的高亮，但由于还没有进行LastActor = ThisActor赋值操作，所以上一个物体还是ThisActor
		{
			ThisActor->UnHighLightActor();
			return;	
		}
	}
	//ThisActor是当前指向的Actor，LastActor是上一次指向的Actor
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	/*
	 *鼠标事件：
	 *A.鼠标未指向任何拥有IEnemyInterface接口的actor
	 *	-什么也不会发生
	 *B.鼠标第一次指向拥有IEnemyInterface接口的actor
	 *	-ThisActor高亮
	 *C.鼠标之前指向了拥有IEnemyInterface接口的actor，现在没有指向IEnemyInterface接口的actor
	 *	-LastActor取消高亮
	 *D.鼠标之前指向了拥有IEnemyInterface接口的actor，现在也指向IEnemyInterface接口的actor，但是不是同一个
	 *	-LastActor取消高亮，ThisActor高亮
  	 *E.鼠标之前指向了拥有IEnemyInterface接口的actor，现在也指向IEnemyInterface接口的actor，是同一个
	 *	-ThisActor高亮或者什么都不做,其实什么都不做都行，因为先前的也没取消高亮，如果相同的话就还是亮着的
	 */
	if(LastActor == nullptr)	//Last为空
	{
		if(ThisActor != nullptr)
		{
			ThisActor->HighLightActor();		//情况B
		}else
		{
			return;								//情况A
		}
	}
	else//Last不为空
	{
		if(ThisActor == nullptr)
		{
			LastActor->UnHighLightActor();	//情况C
		}
		else
		{
			if(ThisActor != LastActor)
			{
				LastActor->UnHighLightActor();		//情况D
				ThisActor->HighLightActor();
			}else
			{
				//情况E
				return;
			}
		}
	}
}


void AAuraPlayerController::MoveFunction(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator	YawRotation(0.f, Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
