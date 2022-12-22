// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UObject/UObjectGlobals.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PatrolTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SUDDENATTACK_API UPatrolTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPatrolTask(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search")
	float search_radius = 1500.f;
	
};
