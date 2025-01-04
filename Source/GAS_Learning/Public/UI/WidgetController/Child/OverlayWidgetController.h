// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature,float,NewMaxMana);
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class GAS_LEARNING_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangeSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthChangeSignature OnMaxHealthChange;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangeSignature OnManaChange;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaChangeSignature OnMaxManaChange;

public:
	//初始化数据以及绑定监听
	virtual void BroadcastInitialValues() override;

	virtual void BindListeningEvents() override;

	//AS组件属性改变事件
	void HealthIsChange(const FOnAttributeChangeData& Data) const;

	void MaxHealthIsChange(const FOnAttributeChangeData& Data) const;

	void ManaIsChange(const FOnAttributeChangeData& Data) const;

	void MaxManaIsChange(const FOnAttributeChangeData& Data) const;
};
