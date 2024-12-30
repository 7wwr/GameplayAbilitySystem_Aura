// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Aura.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_API AAura : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAura();
protected:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;
public:
	//用于初始化GAS组件的函数
	void InitAbilitySystem();
	//服务端开始分配控制器时调用该函数，可用于初始化GAS组件
	virtual void PossessedBy(AController* NewController) override;
	//PlayerState变化时调用的回调函数
	virtual void OnRep_PlayerState() override;

	
};
