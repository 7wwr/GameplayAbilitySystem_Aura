// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	

}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::AppleEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	check(GameplayEffectClass);
	//使用转化成接口的方式来判断Target里面是否实现了AbilitySystemComponent组件。（废弃，因为要学习使用静态函数）
	/*
		IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Target);
		if (AbilitySystemInterface)
		{
			AbilitySystemInterface->GetAbilitySystemComponent()
		}
	*/
	//使用静态函数获取ASC组件
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC)
	{
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle);
		//使用ActiveEffectHandle句柄来储存活跃的效果对应的句柄
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*(EffectSpecHandle.Data.Get()));
		//判断是否为无限效果（也可以通过这一方式来修改效果类型，但非常不建议在运行时修改类型）
		const bool BIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy ==EGameplayEffectDurationType::Infinite;
		//是无限效果就进入if
		if(BIsInfinite)
		{
			IsInfiniteEffect(ActiveEffectHandle,TargetASC);
		}
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		AppleEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		AppleEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		AppleEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	/*
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		AppleEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		AppleEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	*/
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveInfiniteEffect(TargetActor);
	}
}

void AAuraEffectActor::IsInfiniteEffect(const FActiveGameplayEffectHandle& ActiveEffectHandle , UAbilitySystemComponent* SelfASC)
{
	//如果是可以终止的无限效果
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveGameplayEffectsMap.Add(ActiveEffectHandle ,SelfASC);
	}
}

void AAuraEffectActor::RemoveInfiniteEffect(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(!IsValid(TargetASC)) return;
	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	//删除ASC组件中的效果
	for(auto HandlePair : ActiveGameplayEffectsMap)
	{
		if(TargetASC == HandlePair.Value)
		{
			TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
			HandlesToRemove.Add(HandlePair.Key);
		}
	}
	//删除还在Map中的句柄
	for(auto HandlePair : HandlesToRemove)
	{
		ActiveGameplayEffectsMap.FindAndRemoveChecked(HandlePair);
	}
}












