// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/Child/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChange.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChange.Broadcast(AuraAttributeSet->GetMaxMana());

	// 开始监听
	BindListeningEvents();
}

void UOverlayWidgetController::BindListeningEvents()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	//创建生命值变动监听事件
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
												.AddUObject(this,&UOverlayWidgetController::HealthIsChange);
	//创建最大生命值变动监听事件
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
												.AddUObject(this,&UOverlayWidgetController::MaxHealthIsChange);
	//创建法力值变动监听事件
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
												.AddUObject(this,&UOverlayWidgetController::ManaIsChange);
	//创建最大法力值变动监听事件
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
												.AddUObject(this,&UOverlayWidgetController::MaxManaIsChange);
	
}

void UOverlayWidgetController::HealthIsChange(const FOnAttributeChangeData& Data) const
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthIsChange(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaIsChange(const FOnAttributeChangeData& Data) const
{
	OnManaChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaIsChange(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChange.Broadcast(Data.NewValue);
}
