// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere,Category= "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category= "Input")
	TObjectPtr<UInputAction> MoveAction;

	//这里为什么把指针设为IEnemyInterface，个人认为是需要这俩变量的功能也仅仅是为了高亮目标，而使用IEnemyInterface接口
	//能保证只调用到那两个高亮功能的函数（多继承特性，通过基类指针只能调用到基类声明的函数，无法查询其他基类以及派生类实现的自己独有的函数）
	//其实不是的，意思是只要有这个接口的Actor都符合，没那么多讲究
	TObjectPtr<IEnemyInterface> LastActor;
	TObjectPtr<IEnemyInterface> ThisActor;

	//移动事件
	void MoveFunction(const FInputActionValue& InputActionValue);

	//鼠标选取对象
	void CursorTrace();
	
};

