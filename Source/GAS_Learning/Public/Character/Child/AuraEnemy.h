// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Interaction/EnemyInterface.h>

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAS_LEARNING_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	
	virtual void HighLightActor() override;
	
	virtual void UnHighLightActor() override;


};
