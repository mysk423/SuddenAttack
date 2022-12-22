// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolTask.h"
#include "NavigationSystem.h"
#include "SDAiController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UPatrolTask::UPatrolTask(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("PatrolPos");
}

EBTNodeResult::Type UPatrolTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<ASDAiController>(OwnerComp.GetAIOwner());
	auto Enemy = Controller->GetPawn();

	if (nullptr == Enemy)
	{
		return EBTNodeResult::Failed;
	}
	//현재 에디터에 설정된 navimesh로 초기화

	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FVector const Origin = Enemy->GetActorLocation();
	FNavLocation NextPatrol;

	//nextPatrol변수에 임의의 location 값을 넣고 다시 targetlocation키의 value에 값을 넣는다.
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, search_radius, NextPatrol, nullptr))
	{
		Controller->get_blackboard()->SetValueAsVector(ASDAiController::TargetLocation, NextPatrol.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
