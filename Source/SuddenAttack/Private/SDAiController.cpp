// Fill out your copyright notice in the Description page of Project Settings.


#include "SDAiController.h"
#include "..\Public\SDAiController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SDPlayerCharacter.h"
#include "BlackBoardKey.h"

const FName ASDAiController::PosKey(TEXT("HomePos"));
const FName ASDAiController::TargetLocation(TEXT("TargetLocation"));

ASDAiController::ASDAiController(FObjectInitializer const& object_initilizer) {
	//ConstructorHelpers로 에디터에 미리 만들어둔 비헤이비어트리를 지정
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/SuddenAttackProject/BluePrint/Ai/BT_Ai.BT_Ai'"));
	if (BTObject.Succeeded())
	{
		btree = BTObject.Object;
	}
	behaiver_tree_component = object_initilizer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initilizer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	SetPerceptionSystem();
}

void ASDAiController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(btree);
	behaiver_tree_component->StartTree(*btree);
}

void ASDAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

UBlackboardComponent* ASDAiController::get_blackboard() const
{
	return blackboard;
}

void ASDAiController::OnUpdated(TArray<AActor*> const& updated_actors)
{
}

void ASDAiController::OnTargetDetected(AActor* actor, FAIStimulus const Stimulus)
{
	if (auto const player = Cast<ASDPlayerCharacter>(actor))
	{
		get_blackboard()->SetValueAsBool(BB_keys::can_see_player, Stimulus.WasSuccessfullySensed());
	}
}

void ASDAiController::SetPerceptionSystem()
{
	SightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));

	SightConfig->SightRadius = AiSightRadius;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + AiLoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AiFieldOfView;
	SightConfig->SetMaxAge(AiSightAge);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = AiLastSeenLocation;

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ASDAiController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
