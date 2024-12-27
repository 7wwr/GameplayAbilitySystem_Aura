// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	//从IAbilitySystemInterface接口继承来的GetAbilitySystemComponent()，用于获取能力组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//自己创的，假装和上面虚函数一样（bushi），和上面功能一样，返回该类中的组件的
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;	//声明ASC组件，用于玩家

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;		//声明AS组件，理由同上
};
