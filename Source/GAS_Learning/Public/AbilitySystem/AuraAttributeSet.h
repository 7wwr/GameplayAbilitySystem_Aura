// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();

protected:
	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/********************健康值***********************/
	//当前健康值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attribute")
	FGameplayAttributeData Health;
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	
	//当前健康值的回调函数
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//最大健康值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attribute")
	FGameplayAttributeData MaxHealth;
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);

	//最大健康值的回调函数
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	/*--------------------------------------------------*/

	/********************Mana法力值***********************/
	//当前法力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attribute")
	FGameplayAttributeData Mana;
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana);

	//当前法力值的回调函数
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//最大法力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attribute")
	FGameplayAttributeData MaxMana;
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxMana);

	//最大法力值的回调函数
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	/*--------------------------------------------------*/
	
};
