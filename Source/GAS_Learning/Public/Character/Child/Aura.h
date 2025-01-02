// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Aura.generated.h"

class UAuraAttributeSet;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_API AAura : public AAuraCharacterBase
{
	GENERATED_BODY()

//系统重载函数和构造函数
public:
	AAura();
//自定义变量
protected:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	/*这四个是玩家的属性，用来初始化HUD使用
	 *这两个在父类里面声明过了，这里只是作为提醒类里面有这些变量
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;	//声明ASC组件，用于所有角色，但是分情况Create（玩家的不创建）

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;		//声明AS组件，理由同上
	*/

	//这俩名起成这样是因为父类（APawn）里面有同名变量
	UPROPERTY()
	TObjectPtr<APlayerController> ThisPlayerController;

	UPROPERTY()
	TObjectPtr<APlayerState> ThisPlayerState;
	
//自定义函数
public:
	//用于初始化GAS组件的函数
	void InitAbilitySystem();
	//初始化HUD组件（玩家信息）
	void InitHUDSystem();
	//初始化所有的所需组件,也就是用来集中调用每个小系统的函数，省的写的乱七八糟的
	void InitAnyNeeded();
	//服务端开始分配控制器时调用该函数，可用于初始化GAS组件
	virtual void PossessedBy(AController* NewController) override;
	//PlayerState变化时调用的回调函数
	virtual void OnRep_PlayerState() override;
	
	
};
