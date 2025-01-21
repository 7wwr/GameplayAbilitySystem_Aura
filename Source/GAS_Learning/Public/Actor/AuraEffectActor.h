// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffect;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply,
};
//只有无限效果才会使用该选项，因为其他效果会自动移除，无限需要手动移除
UENUM(BlueprintType)
enum class EEffectRemovalPolicy:uint8
{
	RemoveOnEndOverlap,
	DoNotRemove,
};

UCLASS()
class GAS_LEARNING_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	bool bDestroyEffectActor = false;

	TMap<FActiveGameplayEffectHandle ,UAbilitySystemComponent*> ActiveGameplayEffectsMap;
	//物品等级
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="ActorLevel")
	float ActorLevel = 1.f;

	//即时效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//持续效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//无限效果
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="AuraEffect")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;

	
protected:
	UFUNCTION(BlueprintCallable, Category="AuraEffect")
	void AppleEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable, Category="AuraEffect")
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable, Category="AuraEffect")
	void OnEndOverlap(AActor* TargetActor);

	void IsInfiniteEffect(const FActiveGameplayEffectHandle& ActiveEffectHandle, UAbilitySystemComponent* SelfASC);

	void RemoveInfiniteEffect(AActor* TargetActor);
};
