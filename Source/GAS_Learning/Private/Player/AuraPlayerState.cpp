// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include "AbilitySystem/AuraAbilitySystemComponentBase.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponentBase>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);	//使用Mixed

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	NetUpdateFrequency = 100.f;		//用于网络同步的重要属性，它定义了每秒更新网络数据的频率（即每秒发送的网络包数量）,控制着对象在网络上的更新速率。
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
