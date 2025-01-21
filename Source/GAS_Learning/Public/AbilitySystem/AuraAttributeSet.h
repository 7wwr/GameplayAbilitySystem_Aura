// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
  
/**
 * 
 */

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	//源
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	//对象
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};


UCLASS()
class GAS_LEARNING_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();

protected:
	//预修改
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	//Effect运用后回调
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	/********************健康值***********************/
	//当前健康值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	
	//当前健康值的回调函数
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	//最大健康值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	//最大健康值的回调函数
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	/*--------------------------------------------------*/

	/********************Mana法力值***********************/
	//当前法力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attribute")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	//当前法力值的回调函数
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//最大法力值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	//最大法力值的回调函数
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	/*--------------------------------------------------*/

private:
	void SetEffectPropertiesStruct(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
