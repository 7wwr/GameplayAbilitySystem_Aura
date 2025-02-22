// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class GAS_LEARNING_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	//从IAbilitySystemInterface接口继承来的GetAbilitySystemComponent()，用于获取能力组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//自己创的，假装和上面虚函数一样（bushi），和上面功能一样，返回该类中的组件的
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;	//声明ASC组件，用于所有角色，但是分情况Create（玩家的不创建）

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;		//声明AS组件，理由同上
};
